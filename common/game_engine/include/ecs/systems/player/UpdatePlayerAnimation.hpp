/*
** EPITECH PROJECT, 2024
** Rtype [WSL: Ubuntu]
** File description:
** sysdrawable
*/

#pragma once
#include "ecs/Registry.hpp"
#include "ecs/components/allComponents.hpp"
#include "containers/zipper/Zipper.hpp"
#include "Context.hpp"
#include "InputQueue.hpp"

namespace fsystem {
    class UpdatePlayerAnimation {
    public:
        void operator()(Registry &r, SparseArray<component::Drawable> &drawables,
                SparseArray<component::Controllable> &controllables,
                SparseArray<component::Player> &players) const {
            InputQueue inputQueue;

            for (auto &&[draw, contro, player] : Zipper(drawables, controllables, players)) {
                inputQueue = *player.inputQueue;
                while (!inputQueue.isEmpty()) {
                    InputEvent input = inputQueue.getInputEvent();
                    if (input.type == KeyType::KEYUP && (input.key == contro.upKey || input.key == contro.downKey))
                        draw.nextAnimation = "idle";
                    else if (input.key == contro.downKey)
                        draw.nextAnimation = "down";
                    else if (input.key == contro.upKey)
                        draw.nextAnimation = "up";
                }
            }
        }
    };
}