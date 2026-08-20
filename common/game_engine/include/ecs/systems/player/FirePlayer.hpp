/*
** EPITECH PROJECT, 2024
** Rtype [WSL: Ubuntu]
** File description:
** FireSystem
*/

#pragma once

#include "containers/zipper/Zipper.hpp"
#include "containers/SparseArray.hpp"
#include "ecs/Registry.hpp"
#include "ecs/components/allComponents.hpp"
#include "Context.hpp"
#include "InputQueue.hpp"
#include "entity/player/PlayerProjectile.hpp"

#include "ecs/constantECS.hpp"

namespace fsystem {
    class FirePlayer {
        public:
        void operator()(Registry &r, SparseArray<component::Position> &positions,
                SparseArray<component::Controllable> &controllables,
                SparseArray<component::Player> &players) const {
            InputQueue inputQueue;

            for (auto &&[pos, contro, player] : Zipper(positions, controllables, players)) {
                inputQueue = *player.inputQueue;
                while (!inputQueue.isEmpty())
                    handleProjectileInput(r, pos, contro, inputQueue.getInputEvent(), player);
            }
        }

    private:
        void handleProjectileInput(Registry &r, component::Position &pos,
                component::Controllable &contro, const InputEvent &input, component::Player &player) const {
            if (input.type == KeyType::KEYDOWN && input.key == contro.shootKey && input.repeat == false)
                player.lastTime = input.timestampSec;
            if (input.state != KeyState::RELEASED || input.key != contro.shootKey)
                return;
            double currentTime = input.timestampSec;
            if (currentTime - player.cooldown < PLAYER_FIRE_RATE_S)
                return;
            double percentage = (currentTime - player.lastTime) / PLAYER_POWER_MAX_TIME;
            entity::Projectile e = entity::getPlayerProj((percentage >= 1.0F) ? 1.0F : percentage);
            e.position.x = pos.x + PLAYER_WIDTH;
            e.position.y = pos.y + PLAYER_HEIGHT - e.collidable.h;
            r.createEntity(e);
            player.lastTime = currentTime;
            player.cooldown = currentTime;
        }
    };
}