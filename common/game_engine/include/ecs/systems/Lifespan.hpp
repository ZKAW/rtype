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

namespace fsystem {
    class Lifespan {
    public:
        void operator()(Registry &r, SparseArray<component::Lifespan> &lifespans) const {
            Context context = r.getContext<Context>();

            for (auto &&[id, lifespan] : IndexedZipper(lifespans)) {
                lifespan.time -= context.deltaTimeSeconds;
                if (lifespan.time <= 0)
                    r.killEntity(id);
            }
        }
    };
}
