/*
** EPITECH PROJECT, 2024
** Rtype [WSL: Ubuntu]
** File description:
** PlatPlatIA
*/

#pragma once

#include "containers/zipper/Zipper.hpp"
#include "containers/SparseArray.hpp"
#include "ecs/Registry.hpp"
#include "ecs/components/allComponents.hpp"
#include "Context.hpp"

#define PATAPATA_SWITCH_TIME 1.5F

#include <cstdlib>

namespace fsystem {
    class PlatPlatIA {
    public:
        void operator()(Registry &r, SparseArray<component::Velocity> &velocities, SparseArray<component::Enemy> &enemies, SparseArray<component::AI> &ais) const {
            Context context = r.getContext<Context>();

            for (auto &&[vel, enemy, ai] : Zipper(velocities, enemies, ais)) {
                if (enemy.type == EnemyType::PATAPATA) {
                    ai.elapsedTime += context.deltaTimeSeconds;
                    if (ai.elapsedTime >= PATAPATA_SWITCH_TIME) {
                        vel.vy = (rand() % 200 - 100) / 100.0F * PATAPATA_SPEED_VY;
                        ai.elapsedTime = 0;
                    }
                }
            }
        }
    };
}