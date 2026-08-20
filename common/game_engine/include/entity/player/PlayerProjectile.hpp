/*
** EPITECH PROJECT, 2024
** Rtype [WSL: Ubuntu]
** File description:
** PlayerProjectile
*/

#include "ecs/components/allComponents.hpp"
#include "../EntityProjectile.hpp"

namespace entity {
    entity::Projectile getPlayerProj(double strengthPercentage);
    std::map<std::string, component::Animation> getPlayerProjAnimations(void);
}
