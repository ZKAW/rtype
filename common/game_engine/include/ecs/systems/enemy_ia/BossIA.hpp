/*
** EPITECH PROJECT, 2024
** Rtype [WSL: Ubuntu]
** File description:
** BossIA
*/

#pragma once

#include "containers/zipper/Zipper.hpp"
#include "containers/SparseArray.hpp"
#include "ecs/Registry.hpp"
#include "ecs/components/allComponents.hpp"
#include "Context.hpp"

#define BOSS_SWITCH_TIME 1.5f

#include <cstdlib>

namespace fsystem {
    class BossIA {
    public:
        void operator()(Registry &r, SparseArray<component::Velocity> &velocities, SparseArray<component::Enemy> &enemies, SparseArray<component::AI> &ais) const {
            Context context = r.getContext<Context>();

            for (auto &&[vel, enemy, ai] : Zipper(velocities, enemies, ais)) {
                if (enemy.type == EnemyType::BOSS) {
                    ai.elapsedTime += context.deltaTimeSeconds;
                    if (ai.elapsedTime >= BOSS_SWITCH_TIME) {
                        vel.vy = 0;
                        ai.elapsedTime = 0;
                    }
                }
            }
        }
    };
}
