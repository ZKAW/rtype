/*
** EPITECH PROJECT, 2024
** Rtype [WSL: Ubuntu]
** File description:
** PositionSystem
*/

#pragma once

#include "containers/zipper/Zipper.hpp"
#include "containers/SparseArray.hpp"
#include "ecs/Registry.hpp"
#include "ecs/components/allComponents.hpp"
#include "Context.hpp"

namespace fsystem {
    class Position {
    public:
        void operator()(Registry &r, SparseArray<component::Position> &positions, SparseArray<component::Velocity> &velocities) const {
            Context context = r.getContext<Context>();

            for (auto &&[pos, vel] : Zipper(positions, velocities)) {
                pos.x += (vel.vx * context.deltaTimeSeconds);
                pos.y += (vel.vy * context.deltaTimeSeconds);
            }
        }
    };
}
