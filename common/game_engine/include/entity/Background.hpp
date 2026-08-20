/*
** EPITECH PROJECT, 2024
** Rtype [WSL: Ubuntu]
** File description:
** Background
*/

#pragma once

#include <tuple>
#include "ecs/components/allComponents.hpp"

namespace entity {
    using AnimationMap = std::map<std::string, component::Animation>;
    struct Background {
        component::Position position;
        component::Drawable drawable;
        component::Background background;

        auto as_tuple() {
            return std::tie(position, drawable, background);
        }
    };

    Background getBackground(int width, int height);
    auto getBackgroundAnimations(int width, int height);
}