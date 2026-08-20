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
    class ClearInput {
    public:
        void operator()(Registry &r, SparseArray<component::Player> &players) const {
            for (auto &&[player] : Zipper(players)) {
                player.inputQueue->reset();
            }
        }
    };
}
