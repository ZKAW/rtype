#pragma once
#include "entity/EntityProjectile.hpp"
#include <map>
#include <string>
#include <filesystem>
#include "ecs/components/allComponents.hpp"

namespace entity {
    Projectile getEnemyProj();
    std::map<std::string, component::Animation> getEnemyProjAnimations(void);
    Projectile getBossProj();
    std::map<std::string, component::Animation> getBossProjAnimations(void);
}
