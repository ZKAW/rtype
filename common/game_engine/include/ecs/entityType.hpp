/*
** EPITECH PROJECT, 2024
** Rtype [WSL: Ubuntu]
** File description:
** entityType
*/

#pragma once

#include "ecs/Registry.hpp"
#include "components/allComponents.hpp"

enum EntityType {
    PLAYER,
    ENEMY,
    PROJECTILE,
    BOOSTER,
    NONE
};

EntityType getEntityType(Registry &r, size_t id);
