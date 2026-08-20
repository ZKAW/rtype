/*
** EPITECH PROJECT, 2024
** Rtype [WSL: Ubuntu]
** File description:
** components
*/

#pragma once

#include <cstdint>
#include <filesystem>
#include "InputQueue.hpp"

namespace component {
    struct Player {
        uint16_t clientId;
        std::shared_ptr<InputQueue> inputQueue = std::make_shared<InputQueue>();
        int score;
        bool alive = true;

        // For shooting
        double lastTime = 0;
        double cooldown = 0;
    };
}
