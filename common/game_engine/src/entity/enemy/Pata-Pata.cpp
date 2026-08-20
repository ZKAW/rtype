/*
** EPITECH PROJECT, 2024
** Rtype [WSL: Ubuntu]
** File description:
** Pata-Pata
*/

#include "entity/enemy/Enemy.hpp"
#include <map>

#include "ecs/constantECS.hpp"

namespace entity {
std::map<std::string, component::Animation> getEnemyAnimations()
{
    std::map<std::string, component::Animation> anims;
    std::filesystem::path texture_path = "client/sprites/enemy/pata-pata.gif";
    int frame_width = PATAPATA_WIDTH;
    int frame_height = PATAPATA_HEIGHT;

    anims["idle"] = component::Animation{
        .texture = texture_path.string(),
        .xOrigin = 231,
        .srcRect = {
            .x = 231,
            .y = 0,
            .w = frame_width,
            .h = frame_height
        },
        .destRect = {
            .x = 0,
            .y = 0,
            .w = frame_width,
            .h = frame_height
        },
        .frameCount = 8,
        .frameWidth = frame_width,
        .frameDuration = 0.2F,
        .loop = true,
        .leftToRight = false
    };

    return anims;
}

Enemy getPataPata(float x, float y, unsigned int life_multiplier) {
    return Enemy {
        .position = component::Position{.x = x, .y = y},
        .velocity = component::Velocity{.vx = PATAPATA_SPEED_VX, .vy = PATAPATA_SPEED_VY},
        .collidable = component::Collidable{.w = PATAPATA_WIDTH, .h = PATAPATA_HEIGHT},
        .drawable = component::Drawable{
            .currentAnimation = "idle",
            .nextAnimation = "idle",
            .animations = getEnemyAnimations(),
            .zIndex = ENEMY_ZINDEX
        },
        .health = component::Health{
            .currentHealth = static_cast<int>(PATAPATA_HEALTH * life_multiplier),
            .maxHealth = static_cast<unsigned>(PATAPATA_HEALTH * life_multiplier)
        },
        .enemy = component::Enemy{.type = EnemyType::PATAPATA},
    };
}
}
