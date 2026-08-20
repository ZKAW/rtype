/*
** EPITECH PROJECT, 2024
** Rtype [WSL: Ubuntu]
** File description:
** Booster
*/

#include "entity/booster/Booster.hpp"
#include <map>

#include "ecs/constantECS.hpp"

namespace entity {
std::map<std::string, component::Animation> getBoosterAnimations()
{
    std::map<std::string, component::Animation> anims;
    std::filesystem::path texture_path = "client/sprites/booster/wiper.gif";
    int frame_width = WIPER_WIDTH;
    int frame_height = WIPER_HEIGHT;

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
        .frameCount = 12,
        .frameWidth = frame_width,
        .frameDuration = 0.2F,
        .loop = true,
        .leftToRight = true
    };

    return anims;
}

Booster getWiper(float x, float y) {
    return Booster {
        .position = component::Position{.x = x, .y = y},
        .velocity = component::Velocity{.vx = WIPER_SPEED_VX, .vy = WIPER_SPEED_VY},
        .collidable = component::Collidable{.w = WIPER_WIDTH, .h = WIPER_HEIGHT},
        .drawable = component::Drawable{
            .currentAnimation = "idle",
            .nextAnimation = "idle",
            .animations = getBoosterAnimations(),
            .zIndex = ENEMY_ZINDEX
        },
    };
}
}
