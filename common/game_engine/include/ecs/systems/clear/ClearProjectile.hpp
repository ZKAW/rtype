/*
** EPITECH PROJECT, 2024
** Rtype [WSL: Ubuntu]
** File description:
** ProjectileSystem
*/

#pragma once

#include "containers/zipper/IndexedZipper.hpp"
#include "containers/SparseArray.hpp"
#include "ecs/Registry.hpp"
#include "ecs/components/allComponents.hpp"
#include "Context.hpp"

#include "clearConstants.hpp"

namespace fsystem {
    class ClearProjectile {
    public:
        void operator()(Registry &r, SparseArray<component::Position> &positions, SparseArray<component::Projectile> &projectiles) const {
            Context context = r.getContext<Context>();

            for (auto &&[id, pos, proj] : IndexedZipper(positions, projectiles)) {
                if (pos.x < 0 || pos.x > RIGHT_BOUND || pos.y < 0 || pos.y > BOTTOM_BOUND)
                    r.killEntity(id);
            }
        }
    };
}
