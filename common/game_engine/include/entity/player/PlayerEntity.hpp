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
    struct Player {
        component::Position position;
        component::Velocity velocity;
        component::Collidable collidable;
        component::Drawable drawable;
        component::Player player;
        component::Controllable controllable;

        auto as_tuple() {
            return std::tie(position, velocity, collidable, drawable, player, controllable);
        }
    };

    std::map<std::string, component::Animation> getPlayerAnimations(void);
    entity::Player getPlayer(uint16_t clientId);
}
