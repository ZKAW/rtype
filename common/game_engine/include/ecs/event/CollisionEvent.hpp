/*
** EPITECH PROJECT, 2024
** Rtype [WSL: Ubuntu]
** File description:
** CollisionEvent
*/

#pragma once

#include "ecs/components/Position.hpp"
#include "ecs/entityType.hpp"
#include <cstddef>

namespace event {
    struct CollisionEvent {
        size_t id1;
        EntityType type1;
        size_t id2;
        EntityType type2;
    };
}
