/*
** EPITECH PROJECT, 2024
** Rtype [WSL: Ubuntu]
** File description:
** Test
*/

#pragma once

#include <tuple>
#include "ecs/components/allComponents.hpp"

namespace entity {
    struct Enemy {
        component::Position position;
        component::Velocity velocity;
        component::Collidable collidable;
        component::Drawable drawable;
        component::Health health;
        component::Enemy enemy;
        component::AI ai;

        auto as_tuple() {
            return std::tie(position, velocity, collidable, drawable, health, enemy, ai);
        }
    };

    std::map<std::string, component::Animation> getEnemyAnimations(void);
    entity::Enemy getPataPata(float x = 0, float y = 0, unsigned int life_multiplier = 1);
    entity::Enemy getQuoicoubax(float x = 0, float y = 0, unsigned int life_multiplier = 1);
    entity::Enemy getBoss(float x = 0, float y = 0, unsigned int life_multiplier = 1);
}
