/*
** EPITECH PROJECT, 2024
** Rtype [WSL: Ubuntu]
** File description:
** Background
*/

#include "entity/Background.hpp"
#include <map>
#include "ecs/constantECS.hpp"

enum BackgroundDimensions {
    kWidth = 460,
    kHeight = 460
};

namespace entity {
auto getBackgroundAnimations(int width, int height)
{
    AnimationMap anims;
    std::filesystem::path texture_path = BACKGROUND_IMAGE;

    anims["idle"] = component::Animation {
        .texture = texture_path.string(),
        .xOrigin = 0,
        .srcRect = {
            .x = 0,
            .y = 0,
            .w = kWidth / 2,
            .h = kHeight
        },
        .destRect = {
            .x = 0,
            .y = 0,
            .w = width,
            .h = height
        },
        .frameCount = kWidth - (kWidth / 2),
        .frameWidth = 1,
        .frameDuration = 0.3F,
        .loop = true
    };

    return anims;
}

Background getBackground(int width, int height) {
    return Background {
        .position = component::Position{.x = 0, .y = 0},
        .drawable = component::Drawable{
            .currentAnimation = "idle",
            .nextAnimation = "idle",
            .animations = getBackgroundAnimations(width, height),
            .zIndex = BACKGROUND_ZINDEX
        },
        .background = component::Background{}
    };
}
}
