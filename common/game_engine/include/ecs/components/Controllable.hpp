/*
** EPITECH PROJECT, 2024
** Rtype [WSL: Ubuntu]
** File description:
** Controllable
*/

#pragma once

#include "InputQueue.hpp"

namespace component {
    struct Controllable {
        InputKey upKey;
        InputKey downKey;
        InputKey leftKey;
        InputKey rightKey;
        InputKey shootKey;
        float speed; // pixels per second
    };
} // namespace component
