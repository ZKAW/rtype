#include "entity/enemy/EnemyProjectile.hpp"
#include "ecs/constantECS.hpp"

namespace entity {
std::map<std::string, component::Animation> getEnemyProjAnimations()
{
    std::map<std::string, component::Animation> anims;
    std::filesystem::path texture = "client/sprites/proj.gif";

    anims["idle"] = component::Animation {
        .texture = texture.string(),
        .xOrigin = 134,
        .srcRect = {
            .x = 134,
            .y = 6,
            .w = 16,
            .h = 6
        },
        .destRect = {
            .x = 0,
            .y = 0,
            .w = 16,
            .h = 6
        },
        .frameCount = 5,
        .frameWidth = 16,
        .frameDuration = 0.1F,
        .loop = true
	};

    return anims;
}

Projectile getEnemyProj() {
    return Projectile {
        .position = component::Position{
            .x = 0,
            .y = 0
        },
        .velocity = component::Velocity{
            .vx = -200,
            .vy = 0
        },
        .collidable = component::Collidable{
            .w = 16,
            .h = 16
        },
        .drawable = component::Drawable{
            .currentAnimation = "idle",
            .nextAnimation = "idle",
            .animations = getEnemyProjAnimations(),
            .zIndex = PROJECTILE_ZINDEX
        },
        .projectile = component::Projectile{
            .damage = 10,
            .isPlayerProjectile = false
        }
    };
}

}
