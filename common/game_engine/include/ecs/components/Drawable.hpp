/*
** EPITECH PROJECT, 2024
** Rtype [WSL: Ubuntu]
** File description:
** Drawable
*/
#pragma once

#include <filesystem>
#include <memory>
#include <map>
#include "InputQueue.hpp"

namespace component {

    struct Rect {
        int x;
        int y;
        int w;
        int h;
    };

    struct Animation {
        std::string texture;
        int xOrigin;
        Rect srcRect;
        Rect destRect;
        int frameCount;
        int frameWidth;
        double frameDuration; // seconds
        bool loop;

        bool leftToRight = true;
        int currentFrame = 0;
        double elapsedTime = 0.0F; // seconds
    };

    struct Drawable {
        std::string currentAnimation;
        std::string nextAnimation;
        std::map<std::string, Animation> animations;
        int zIndex;
    };
} // namespace component
