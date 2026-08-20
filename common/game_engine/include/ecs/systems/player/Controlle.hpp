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
#include "Context.hpp"
#include "InputQueue.hpp"

namespace fsystem {
    class Controlle {
    public:
        void operator()(Registry &r, SparseArray<component::Velocity> &velocities,
                SparseArray<component::Controllable> &controllables,
                SparseArray<component::Player> &players) const {
            InputQueue inputQueue;

            for (auto &&[vel, contro, player] : Zipper(velocities, controllables, players)) {
                inputQueue = *player.inputQueue;
                while (!inputQueue.isEmpty())
                    handleMovementInput(vel, contro, inputQueue.getInputEvent());
            }
        }

    private:
        void handleMovementInput(component::Velocity &vel, component::Controllable &contro, const InputEvent &input) const {
            if (input.type == KeyType::KEYDOWN) {
                if (input.key == contro.upKey)
                    vel.vy = -contro.speed;
                else if (input.key == contro.downKey)
                    vel.vy = contro.speed;
                else if (input.key == contro.leftKey)
                    vel.vx = -contro.speed;
                else if (input.key == contro.rightKey)
                    vel.vx = contro.speed;
            } else if (input.type == KeyType::KEYUP) {
                if (input.key == contro.upKey || input.key == contro.downKey)
                    vel.vy = 0;
                else if (input.key == contro.leftKey || input.key == contro.rightKey)
                    vel.vx = 0;
            }
        }
    };
}