#pragma once
#include "ecs/Registry.hpp"
#include "ecs/components/allComponents.hpp"
#include "entity/EntityProjectile.hpp"
#include "ecs/constantECS.hpp"
#include <random>
#include "containers/zipper/Zipper.hpp"
#include "entity/enemy/EnemyProjectile.hpp"

namespace fsystem {
    class FireEnemy {
    public:
        void operator()(Registry &r, SparseArray<component::Position> &positions,
                SparseArray<component::Enemy> &enemies) const {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<> dis(0.0, 1.0);

            for (auto &&[pos, enemy] : Zipper(positions, enemies)) {
                //if (dis(gen) < 0.005 && pos.y != BOSS_POS_Y && pos.x != BOSS_POS_X) {
                if (dis(gen) < FIRE_RATE_EN && enemy.type != EnemyType::BOSS) {
                    auto e = entity::getEnemyProj();
                    e.position.x = pos.x - 16;
                    e.position.y = pos.y + 16;
                    r.createEntity(e);
                }
                if (dis(gen) < FIRE_RATE_BOSS && enemy.type == EnemyType::BOSS) {
                    auto e = entity::getBossProj();
                    e.position.x = pos.x + BOSS_WIDTH / 2;
                    e.position.y = pos.y + BOSS_HEIGHT / 2;
                    e.velocity.vx = -50;
                    e.velocity.vy = 10;
                    r.createEntity(e);
                    e.velocity.vy = -10;
                    r.createEntity(e);
                    e.velocity.vy = 0;
                    r.createEntity(e);
                }
            
            }
        }
    };
}
