/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Boss
*/

#include <map>

#include "entity/enemy/Enemy.hpp"
#include "ecs/constantECS.hpp"

namespace {
    std::map<std::string, component::Animation> getBossAnimations()
    {
        std::map<std::string, component::Animation> anims;
        std::filesystem::path texture_path = "client/sprites/enemy/boss.gif";
        int frame_width = BOSS_WIDTH;
        int frame_height = BOSS_HEIGHT;

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
            .frameCount = 4,
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

entity::Enemy entity::getBoss(float x, float y, unsigned int life_multiplier)
{
    return entity::Enemy {
        .position = component::Position{
            .x = x,
            .y = y
        },
        .velocity = component::Velocity{
            .vx = 0,
            .vy = 0
        },
        .collidable = component::Collidable{
            .w = BOSS_WIDTH,
            .h = BOSS_HEIGHT
        },
        .drawable = component::Drawable{
            .currentAnimation = "idle",
            .nextAnimation = "idle",
            .animations = getBossAnimations(),
            .zIndex = ENEMY_ZINDEX
        },
        .health = component::Health{
            .currentHealth = static_cast<int>(BOSS_HEALTH * life_multiplier),
            .maxHealth = static_cast<unsigned>(BOSS_HEALTH * life_multiplier)
        },
        .enemy = component::Enemy{
            .type = EnemyType::BOSS
        },
    };
}
