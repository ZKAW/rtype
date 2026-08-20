/*
** EPITECH PROJECT, 2024
** Rtype [WSL: Ubuntu]
** File description:
** Background
*/

#include "entity/AnimationDeath.hpp"
#include <map>
#include "ecs/constantECS.hpp"

namespace entity {
namespace {
    std::map<std::string, component::Animation> getBoomAnimation()
    {
        std::map<std::string, component::Animation> anims;
        std::filesystem::path texture_path = DEATH_IMAGE;

        anims["idle"] = component::Animation {
            .texture = texture_path.string(),
            .xOrigin = 127,
            .srcRect = {
                .x = 127,
                .y = 0,
                .w = 33,
                .h = 33
            },
            .destRect = {
                .x = 0,
                .y = 0,
                .w = 33,
                .h = 33
            },
            .frameCount = 6,
            .frameWidth = 33,
            .frameDuration = 0.1F,
            .loop = false
        };

        return anims;
    }
}

AnimationDeath getAnimationDeath(float x, float y) {
    return AnimationDeath {
        .position = component::Position{
            .x = x,
            .y = y
        },
        .drawable = component::Drawable{
            .currentAnimation = "idle",
            .nextAnimation = "idle",
            .animations = getBoomAnimation(),
            .zIndex = 3
        },
        .lifespan = component::Lifespan{
            .time = 0.7F
        }
    };
}
}
