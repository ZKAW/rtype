/*
** EPITECH PROJECT, 2024
** Rtype [WSL: Ubuntu]
** File description:
** PlayerEntitiy
*/

#include "entity/player/PlayerEntity.hpp"
#include <map>

#include "ecs/constantECS.hpp"

namespace entity {
std::map<std::string, component::Animation> getPlayerAnimations()
{
    std::map<std::string, component::Animation> anims;
    std::filesystem::path texture_path = "client/sprites/player/ship.gif";
    int frame_width = PLAYER_WIDTH;
    int frame_height = PLAYER_HEIGHT;

    anims["down"] = component::Animation {
        .texture = texture_path.string(),
        .xOrigin = 34,
        .srcRect = {
            .x = 34,
            .y = 2,
            .w = frame_width,
            .h = frame_height
        },
        .destRect = {
            .x = 0,
            .y = 0,
            .w = frame_width,
            .h = frame_height
        },
        .frameCount = 2,
        .frameWidth = frame_width,
        .frameDuration = 0.2F,
        .loop = false,
        .leftToRight = false
    };

    anims["idle"] = component::Animation {
        .texture = texture_path.string(),
        .xOrigin = 67,
        .srcRect = {
            .x = 67,
            .y = 2,
            .w = frame_width,
            .h = frame_height
        },
        .destRect = {
            .x = 0,
            .y = 0,
            .w = frame_width,
            .h = frame_height
        },
        .frameCount = 1,
        .frameWidth = frame_width,
        .frameDuration = 0.0F,
        .loop = false
    };

    anims["up"] = component::Animation{
        .texture = texture_path.string(),
        .xOrigin = 100,
        .srcRect = {
            .x = 100,
            .y = 2,
            .w = frame_width,
            .h = frame_height
        },
        .destRect = {
            .x = 0,
            .y = 0,
            .w = frame_width,
            .h = frame_height
        },
        .frameCount = 2,
        .frameWidth = frame_width,
        .frameDuration = 0.2F,
        .loop = false
    };
    return anims;
}

Player getPlayer(uint16_t clientId) {
    return Player {
        .position = component::Position{
            .x = PLAYER_DEFAULT_X,
            .y = PLAYER_DEFAULT_Y
        },
        .velocity = component::Velocity{
            .vx = 0.0F,
            .vy = 0.0F
        },
        .collidable = component::Collidable{
            .w = PLAYER_WIDTH,
            .h = PLAYER_HEIGHT
        },
        .drawable = component::Drawable{
            .currentAnimation = "idle",
            .nextAnimation = "idle",
            .animations = getPlayerAnimations(),
            .zIndex = PLAYER_ZINDEX
        },
        .player = component::Player{
            .clientId = clientId,
            .score = 0
        },
        .controllable = component::Controllable{
            .upKey = InputKey::UP,
            .downKey = InputKey::DOWN,
            .leftKey = InputKey::LEFT,
            .rightKey = InputKey::RIGHT,
            .shootKey = InputKey::SPACE,
            .speed = PLAYER_SPEED
        }
    };
}
}
