/*
** EPITECH PROJECT, 2024
** Rtype [WSL: Ubuntu]
** File description:
** PlayerProjectile
*/

#pragma once

#include <tuple>
#include "ecs/components/allComponents.hpp"

namespace entity {
    struct Projectile {
        component::Position position;
        component::Velocity velocity;
        component::Collidable collidable;
        component::Drawable drawable;
        component::Projectile projectile;

        auto as_tuple() {
            return std::tie(position, velocity, collidable, drawable, projectile);
        }
    };
}
