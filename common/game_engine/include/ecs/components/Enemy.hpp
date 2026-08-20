/*
** EPITECH PROJECT, 2024
** Rtype [WSL: Ubuntu]
** File description:
** Enemy
*/

#pragma once

#include "entity/enemy/EnemyType.hpp"

namespace component {
    struct Enemy {
        EnemyType type;
        bool alive = true;
    };
} // namespace component
