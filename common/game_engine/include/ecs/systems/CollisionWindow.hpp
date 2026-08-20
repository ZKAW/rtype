/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** CollisionWindow
*/

#pragma once

#include "containers/zipper/IndexedZipper.hpp"
#include "containers/SparseArray.hpp"
#include "ecs/components/Collidable.hpp"
#include "ecs/Registry.hpp"
#include "ecs/components/allComponents.hpp"
#include "entity/AnimationDeath.hpp"
#include "ecs/constantECS.hpp"

namespace fsystem {
    class CollisionWindow {
    public:
        void operator()(Registry &r, SparseArray<component::Position> &positions, SparseArray<component::Player> &players) const {
        (void)r;
        for (auto &&[id, pos, player] : IndexedZipper(positions, players))
        {
            if (pos.x < 0) {
                pos.x = 0;
            }
            if (pos.y < 0) {
                pos.y = 0;
            }
            if (pos.x > WINDOW_WIDTH - PLAYER_WIDTH) {
                pos.x = WINDOW_WIDTH - PLAYER_WIDTH;
            }
            if (pos.y > WINDOW_HEIGHT - PLAYER_HEIGHT) {
                pos.y = WINDOW_HEIGHT - PLAYER_HEIGHT;
            }
        }
    }
    };
}
