# ECS

## ECS Pattern Description
ECS design pattern permits to make a clear separation between data and logic. It is a pattern that is used in game development to manage the game state. The ECS pattern is composed of three main components: Entities, Components, and Systems. The Entities are the objects in the game, the Components are the data that is attached to the Entities, and the Systems are the logic that is applied to the Entities. The ECS pattern is used to make the game development process more efficient and to make the code more maintainable. The ECS pattern is used in many game engines, such as Unity and Unreal Engine.

## Entities
Entities are the objects in the game. They are the things that the player interacts with. Entities can be anything from a player character to a tree to a bullet. Entities are composed of Components. Each Entity has a unique identifier that is used to reference it.
Create an entity with:
### How to Create an Entity within the engine
```cpp
createEntity<EnemyParams>({component::Position{5, 2}, component::Health{100}, component::Enemy{
        .type = 1,
        .speed = 1.0F
    }});
```

## Components
Component are used to store de data such as the position, health, and other properties of the Entities. Components are attached to Entities. Components are simple data structures that contain the data that is needed to describe the Entity. Components are used to store the state of the entity at a given time
### Position Component
```cpp
struct Position {
        struct Position {
        float x, y;

        template<class Archive>
        void serialize(Archive& ar, const unsigned int version) {
            ar & x;
            ar & y;
        }
    };
```
Only Stores the x and y position of the entity in a 2D space
the Archive is used to serialize the data to be sent over the network

### Velocity Component
```cpp
struct Velocity {
        float vx, vy;
    };
```
Stores the velocity of the entity in the x and y axis.

### Projectile Component
```cpp
struct Projectile {
        float x, y;
        float dx, dy;
        float speed;
        float damage;
    };
```
Stores the position, velocity, speed and damage of the projectile

### Health Component
```cpp
  struct Health {
        int currentHealth;
        unsigned maxHealth;
    };
```

### Enemy Component
```cpp
    struct Enemy {
        EnemyType type;
    };
```
only stores the type of the enemy

### Controllable Component
```cpp
struct Controllable {
        InputKey upKey;
        InputKey downKey;
        InputKey leftKey;
        InputKey rightKey;
        InputKey shootKey;
        float speed; // pixels per second
    };
```
Stores the keys that the player can use to move and shoot, and the speed of the player
### Player Component
```cpp
struct Player {
        uint16_t clientId;
        std::shared_ptr<InputQueue> inputQueue = std::make_shared<InputQueue>();
        int score;
        int lives;

        // For shooting
        double lastTime = 0;
        double cooldown = 0;
    };
```
Stores the clientId of the player, the score, the lives, the inputQueue, the last time the player shot, and the cooldown of the player
### Collidable Component
```cpp
struct Collidable {
        float w, h;
    };
```
w and h describe the width and height of the entity hitbox

### Drawable Component
```cpp
    struct Drawable {
        std::string currentAnimation;
        std::string nextAnimation;
        std::map<std::string, Animation> animations;
        int zIndex;
    };
```
Stores the current animation, the next animation, a map of animations, and the z index of the entity

### AI Component
```cpp
struct AI {
        double elapsedTime = 0.0F;
    };
```
## Systems
### Draw System
The Draw System is responsible for drawing the entities on the screen. The Draw System iterates over all the entities that have a Drawable component and draws them on the screen. The Draw System is responsible for rendering the entities in the correct order based on their z-index.
```cpp
class DrawSystem {
public:
    void operator()(Registry &r, std::shared_ptr<IGraphicWrapper> &graphic ,std::shared_ptr<SDL_Renderer> &renderer);

private:
    component::Animation &getCurrentAnimation(component::Drawable &draw) const;
    void setRenderQueue(SparseArray<component::Position> &positions, SparseArray<component::Drawable> &drawables);
    std::shared_ptr<SDL_Texture> getTexture(const std::string &path, std::shared_ptr<IGraphicWrapper> &graphic);

    SDL_Rect RectToSDLRect(const component::Rect &rect);

};
```
```cpp
void operator()(Registry &r, std::shared_ptr<IGraphicWrapper> &graphic ,std::shared_ptr<SDL_Renderer> &renderer);
```
The operator() function is the main function of the Draw System. It takes a Registry, a graphic wrapper, and a SDL renderer as arguments. The function iterates over all the entities that have a Drawable component and draws them on the screen.

```cpp
component::Animation &getCurrentAnimation(component::Drawable &draw) const;
```
The getCurrentAnimation function takes a Drawable component as an argument and returns the current animation of the entity.

```cpp
void setRenderQueue(SparseArray<component::Position> &positions, SparseArray<component::Drawable> &drawables);
```
The setRenderQueue function takes two SparseArrays as arguments: one for the positions of the entities and one for the drawables of the entities. The function sets the render queue based on the z-index of the entities.

```cpp
std::shared_ptr<SDL_Texture> getTexture(const std::string &path, std::shared_ptr<IGraphicWrapper> &graphic);
```
The getTexture function takes a path to an image file and a graphic wrapper as arguments. The function loads the image file and returns a SDL texture.

```cpp
SDL_Rect RectToSDLRect(const component::Rect &rect);
```
The RectToSDLRect function takes a Rect component as an argument and returns a SDL_Rect.