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
    struct Booster {
        component::Position position;
        component::Velocity velocity;
        component::Collidable collidable;
        component::Drawable drawable;
        component::Booster booster;

        auto as_tuple() {
            return std::tie(position, velocity, collidable, drawable, booster);
        }
    };

    std::map<std::string, component::Animation> getBoosterAnimations(void);
    entity::Booster getWiper(float x = 0, float y = 0);
}
