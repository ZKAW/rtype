/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Quoicoubax
*/

#include "entity/enemy/Enemy.hpp"
#include <map>

#include "ecs/constantECS.hpp"

namespace {
    std::map<std::string, component::Animation> getQuoiCouBaxAnimations() {
        std::map<std::string, component::Animation> anims;
        std::filesystem::path texture_path = "client/sprites/enemy/quoicoubax.gif";
        int frame_width = QUOICOUBAX_WIDTH;
        int frame_height = QUOICOUBAX_HEIGHT;

        anims["idle"] = component::Animation{
            .texture = texture_path.string(),
            .xOrigin = 0,
            .srcRect = {
                .x = 0,
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
            .leftToRight = true,
            .currentFrame = 0,
            .elapsedTime = 0.0F
        };

        return anims;
    }
}

entity::Enemy entity::getQuoicoubax(float x, float y, unsigned int life_multiplier) {
    return entity::Enemy {
        .position = component::Position{.x = x, .y = y},
        .velocity = component::Velocity{.vx = QUOICOUBAX_SPEED_VX, .vy = QUOICOUBAX_SPEED_VY},
        .collidable = component::Collidable{.w = QUOICOUBAX_WIDTH, .h = QUOICOUBAX_HEIGHT},
        .drawable = component::Drawable{
            .currentAnimation = "idle",
            .nextAnimation = "idle",
            .animations = getQuoiCouBaxAnimations(),
            .zIndex = ENEMY_ZINDEX
        },
        .health = component::Health{
            .currentHealth = static_cast<int>(QUOICOUBAX_HEALTH * life_multiplier),
            .maxHealth = static_cast<unsigned>(QUOICOUBAX_HEALTH * life_multiplier)
        },
        .enemy = component::Enemy{.type = EnemyType::QUOICOUBAX},
    };
}
