/*
** EPITECH PROJECT, 2024
** Rtype [WSL: Ubuntu]
** File description:
** eventType
*/

#include "ecs/entityType.hpp"

EntityType getEntityType(Registry &r, size_t id) {
    if (r.entityHasComponent<component::Player>(id))
        return EntityType::PLAYER;
    if (r.entityHasComponent<component::Enemy>(id))
        return EntityType::ENEMY;
    if (r.entityHasComponent<component::Projectile>(id))
        return EntityType::PROJECTILE;
    if (r.entityHasComponent<component::Booster>(id))
        return EntityType::BOOSTER;
    return EntityType::NONE;
}
