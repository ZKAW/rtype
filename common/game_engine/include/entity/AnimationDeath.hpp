/*
** EPITECH PROJECT, 2024
** Rtype [WSL: Ubuntu]
** File description:
** AnimationDeath
*/

#pragma once
#include <tuple>
#include "ecs/components/allComponents.hpp"

namespace entity {
    struct AnimationDeath {
        component::Position position;
        component::Drawable drawable;
        component::Lifespan lifespan;

        auto as_tuple() {
            return std::tie(position, drawable, lifespan);
        }

    };
    
    AnimationDeath getAnimationDeath(float x, float y);
}
