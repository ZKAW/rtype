/*
** EPITECH PROJECT, 2024
** Rtype [WSL: Ubuntu]
** File description:
** System
*/

#pragma once

#include "containers/zipper/IndexedZipper.hpp"
#include "containers/SparseArray.hpp"
#include "ecs/Registry.hpp"
#include "ecs/components/allComponents.hpp"
#include "entity/AnimationDeath.hpp"

namespace fsystem {
    class DeathEnemy {
    public:
        void operator()(Registry &r, SparseArray<component::Health> &healths, SparseArray<component::Position> &positions) const {
            for (auto &&[id, health, pos] : IndexedZipper(healths, positions)) {
                if (health.currentHealth <= 0) {
                    r.createEntity(entity::getAnimationDeath(pos.x, pos.y));
                    r.killEntity(id);
                }
            }
        }
    };
}
