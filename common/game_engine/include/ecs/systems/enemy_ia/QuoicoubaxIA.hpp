/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** QUOICOUBAX_IA
*/

#pragma once

#include "containers/zipper/Zipper.hpp"
#include "containers/SparseArray.hpp"
#include "ecs/Registry.hpp"
#include "ecs/components/allComponents.hpp"
#include "Context.hpp"

#include <cstdlib>

namespace fsystem {
    class QUOICOUBAXIA {
    public:
        void operator()(Registry &r, SparseArray<component::Velocity> &velocities, SparseArray<component::Enemy> &enemies, SparseArray<component::AI> &ais) const {
            Context context = r.getContext<Context>();

            for (auto &&[vel, enemy, ai] : Zipper(velocities, enemies, ais)) {
                if (enemy.type == EnemyType::QUOICOUBAX) {
                    ai.elapsedTime += context.deltaTimeSeconds;
                    if (ai.elapsedTime >= QUOICOUBAX_SWITCH_TIME) {
                        vel.vy = (rand() % 200 - 100) / 100.0F * QUOICOUBAX_SPEED_VY;
                        ai.elapsedTime = 0;
                    }
                }
            }
        }
    };
}