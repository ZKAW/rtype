/*
** EPITECH PROJECT, 2024
** Rtype [WSL: Ubuntu]
** File description:
** CollisionSystem
*/

#pragma once

#include "ecs/Registry.hpp"
#include "ecs/components/allComponents.hpp"
#include "containers/zipper/IndexedZipper.hpp"

// #include "event/CollisionEvent.hpp"
#include "ecs/entityType.hpp"
#include "entity/AnimationDeath.hpp"

namespace fsystem {
    class Collision {
    public:
        void operator()(Registry &r, SparseArray<component::Position> &positions, SparseArray<component::Collidable> &Collidables) const {

            for (auto &&[id1, box1, pos1] : IndexedZipper(Collidables, positions)) {
                for (auto &&[id2, box2, pos2] : IndexedZipper(Collidables, positions)) {
                    if (&box1 != &box2 && checkCollision(box1, pos1, box2, pos2)) {
                        handleCollision(r, id1, id2);
                    }
                }
            }
        }
    private:
        bool checkCollision(const component::Collidable &box1, const component::Position &pos1, const component::Collidable &box2, const component::Position &pos2) const {
            return (pos1.x < pos2.x + box2.w &&
                    pos1.x + box1.w > pos2.x &&
                    pos1.y < pos2.y + box2.h &&
                    pos1.y + box1.h > pos2.y);
        }

        void handleCollision(Registry &r, size_t id1, size_t id2) const {
            EntityType e1 = getEntityType(r, id1);
            EntityType e2 = getEntityType(r, id2);

            const auto& projectiles = r.getComponents<component::Projectile>();

            if (e1 == EntityType::PLAYER && e2 == EntityType::PROJECTILE) {
                if (projectiles[id2] && !projectiles[id2]->isPlayerProjectile) {
                    collisionBetweenPlayerAndProjectile(r, id1, id2);
                }
            } else if (e1 == EntityType::PLAYER && e2 == EntityType::ENEMY) {
                collisionBetweenPlayerAndEnemy(r, id1, id2);
            } else if (e1 == EntityType::PLAYER && e2 == EntityType::BOOSTER) {
                collisionBetweenPlayerAndBooster(r, id1, id2);
            } else if (e1 == EntityType::ENEMY && e2 == EntityType::PROJECTILE) {
                if (projectiles[id2] && projectiles[id2]->isPlayerProjectile) {
                    collisionBetweenEnemyAndProjectile(r, id1, id2);
                }
            } else if (e1 == EntityType::PROJECTILE && e2 == EntityType::PLAYER) {
                if (projectiles[id1] && !projectiles[id1]->isPlayerProjectile) {
                    collisionBetweenPlayerAndProjectile(r, id2, id1);
                }
            } else if (e1 == EntityType::PROJECTILE && e2 == EntityType::ENEMY) {
                if (projectiles[id1] && projectiles[id1]->isPlayerProjectile) {
                    collisionBetweenEnemyAndProjectile(r, id2, id1);
                }
            }
        }

        void collisionBetweenPlayerAndProjectile(Registry &r, size_t id1, size_t id2) const {
            r.getComponents<component::Player>()[id1]->alive = false;
            auto &entity = r.getComponents<component::Position>()[id1].value();
            r.createEntity(entity::getAnimationDeath(entity.x, entity.y));
        }

        void collisionBetweenPlayerAndEnemy(Registry &r, size_t id1, size_t id2) const {
            r.getComponents<component::Player>()[id1]->alive = false;
            auto &entity = r.getComponents<component::Position>()[id1].value();
            r.createEntity(entity::getAnimationDeath(entity.x, entity.y));
        }

        void collisionBetweenEnemyAndProjectile(Registry &r, size_t id1, size_t id2) const {
            auto &enemyHealth = r.getComponents<component::Health>()[id1].value();
            auto &projectile = r.getComponents<component::Projectile>()[id2].value();
            enemyHealth.currentHealth -= projectile.damage;
            // kill projectile
            if (enemyHealth.currentHealth >= 0)
                r.killEntity(id2);
        }

        void collisionBetweenPlayerAndBooster(Registry &r, size_t id1, size_t id2) const {
            r.killEntity(id2);

           for (auto &&[id, enemy] : IndexedZipper(r.getComponents<component::Enemy>())) {
                if (enemy.type != EnemyType::BOSS) {
                    auto &entity = r.getComponents<component::Position>()[id].value();
                    r.createEntity(entity::getAnimationDeath(entity.x, entity.y));
                    r.killEntity(id);
                }
           }
        }
    };
}
