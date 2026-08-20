#include "entity/enemy/EnemyProjectile.hpp"
#include "ecs/constantECS.hpp"

namespace entity {
std::map<std::string, component::Animation> getBossProjAnimations()
{
    std::map<std::string, component::Animation> anims;
    std::filesystem::path texture = "client/sprites/bossproj.gif";

    anims["idle"] = component::Animation {
        .texture = texture.string(),
        .xOrigin = 0,
        .srcRect = {
            .x = 0,
            .y = 0,
            .w = 34,
            .h = 34
        },
        .destRect = {
            .x = 0,
            .y = 0,
            .w = 34,
            .h = 34
        },
        .frameCount = 3,
        .frameWidth = 34,
        .frameDuration = 0.1F,
        .loop = true
    };

    return anims;
}

Projectile getBossProj()
{
    return Projectile {
        .position = component::Position{
            .x = 0,
            .y = 0,
        },
        .velocity = component::Velocity{
            .vx = -20,
            .vy = 0
        },
        .collidable = component::Collidable{
            .w = 16,
            .h = 16
        },
        .drawable = component::Drawable{
            .currentAnimation = "idle",
            .nextAnimation = "idle",
            .animations = getBossProjAnimations(),
            .zIndex = PROJECTILE_ZINDEX
        },
        .projectile = component::Projectile{
            .damage = 10,
            .isPlayerProjectile = false
        }
    };
}

}
