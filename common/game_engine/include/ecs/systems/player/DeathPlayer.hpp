/*
** EPITECH PROJECT, 2024
** Rtype [WSL: Ubuntu]
** File description:
** ControlSystem
*/

#pragma once

#include "containers/zipper/Zipper.hpp"
#include "containers/SparseArray.hpp"
#include "ecs/Registry.hpp"
#include "ecs/components/allComponents.hpp"
#include "InputQueue.hpp"

namespace fsystem {
    class DeathPlayer {
    public:
        void operator()(Registry &r, SparseArray<component::Player> &players, SparseArray<component::Position> &positions) const {
            for (auto &&[player, pos] : Zipper(players, positions)) {
                if (player.alive)
                    continue;
                player.alive = true;
                pos.x = 10;
                pos.y = 200;
            }
        }
    };
}
