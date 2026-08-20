/*
** EPITECH PROJECT, 2024
** Rtype [WSL: Ubuntu]
** File description:
** PlayerProjectile
*/

#include "entity/player/PlayerProjectile.hpp"
#include "ecs/constantECS.hpp"

namespace entity {
std::map<std::string, component::Animation> getPlayerProjAnimations()
{
    std::map<std::string, component::Animation> anims;
    std::filesystem::path texture = "client/sprites/player/projectile.gif";

    anims["1"] = component::Animation {
        .texture = texture.string(),
        .xOrigin = 249,
        .srcRect = {.x = 249, .y = 90, .w = 18, .h = 12},
        .destRect = {.x = 0, .y = 0, .w = 18, .h = 12},
        .frameCount = 1,
        .frameWidth = 16,
        .frameDuration = 1000.0F,
        .loop = false
    };

    anims["2"] = component::Animation {
        .texture = texture.string(),
        .xOrigin = 232,
        .srcRect = {.x = 232, .y = 103, .w = 17, .h = 12},
        .destRect = {.x = 0, .y = 0, .w = 17, .h = 12},
        .frameCount = 2,
        .frameWidth = 17,
        .frameDuration = 0.1F,
        .loop = false
    };

    anims["3"] = component::Animation {
        .texture = texture.string(),
        .xOrigin = 200,
        .srcRect = {.x = 200, .y = 120, .w = 33, .h = 12},
        .destRect = {.x = 0, .y = 0, .w = 33, .h = 12},
        .frameCount = 2,
        .frameWidth = 33,
        .frameDuration = 0.1F,
        .loop = false
    };

    anims["4"] = component::Animation {
        .texture = texture.string(),
        .xOrigin = 168,
        .srcRect = {.x = 168, .y = 136, .w = 49, .h = 14},
        .destRect = {.x = 0, .y = 0, .w = 49, .h = 14},
        .frameCount = 2,
        .frameWidth = 49,
        .frameDuration = 0.1F,
        .loop = false
    };

    anims["5"] = component::Animation {
        .texture = texture.string(),
        .xOrigin = 136,
        .srcRect = {.x = 136, .y = 154, .w = 65, .h = 14},
        .destRect = {.x = 0, .y = 0, .w = 65, .h = 14},
        .frameCount = 2,
        .frameWidth = 65,
        .frameDuration = 0.1F,
        .loop = false
    };

    anims["6"] = component::Animation {
        .texture = texture.string(),
        .xOrigin = 104,
        .srcRect = {.x = 104, .y = 170, .w = 81, .h = 16},
        .destRect = {.x = 0, .y = 0, .w = 81, .h = 16},
        .frameCount = 2,
        .frameWidth = 81,
        .frameDuration = 0.1F,
        .loop = false
    };

    return anims;
}

Projectile getPlayerProj(double strengthPercentage) {
    float speed;
    int damage;
    std::string animation;
    component::Collidable collidable;

    if (strengthPercentage < 0.0F || strengthPercentage > 1.0F)
        throw std::runtime_error("getPlayerProj: Invalid strength percentage");
    if (strengthPercentage < PLAYER_PROJECTILE_PERCENTAGE_1) {
        speed = PLAYER_PROJECTILE_SPEED_1;
        damage = PLAYER_PROJECTILE_DAMAGE_1;
        animation = "1";
        collidable.w = 16;
        collidable.h = 4;
    } else if (strengthPercentage < PLAYER_PROJECTILE_PERCENTAGE_2) {
        speed = PLAYER_PROJECTILE_SPEED_2;
        damage = PLAYER_PROJECTILE_DAMAGE_2;
        animation = "2";
        collidable.w = 17;
        collidable.h = 12;
    } else if (strengthPercentage < PLAYER_PROJECTILE_PERCENTAGE_3) {
        speed = PLAYER_PROJECTILE_SPEED_3;
        damage = PLAYER_PROJECTILE_DAMAGE_3;
        animation = "3";
        collidable.w = 33;
        collidable.h = 12;
    } else if (strengthPercentage < PLAYER_PROJECTILE_PERCENTAGE_4) {
        speed = PLAYER_PROJECTILE_SPEED_4;
        damage = PLAYER_PROJECTILE_DAMAGE_4;
        animation = "4";
        collidable.w = 49;
        collidable.h = 14;
    } else if (strengthPercentage < PLAYER_PROJECTILE_PERCENTAGE_5) {
        speed = PLAYER_PROJECTILE_SPEED_5;
        damage = PLAYER_PROJECTILE_DAMAGE_5;
        animation = "5";
        collidable.w = 65;
        collidable.h = 14;
    } else {
        speed = PLAYER_PROJECTILE_SPEED_5;
        damage = PLAYER_PROJECTILE_DAMAGE_5;
        animation = "6";
        collidable.w = 81;
        collidable.h = 16;
    }

    return entity::Projectile {
        .position = component::Position{.x = 0.0F, .y = 0.0F},
        .velocity = component::Velocity{.vx = speed, .vy = 0.0F},
        .collidable = collidable,
        .drawable = component::Drawable{
            .currentAnimation = animation,
            .nextAnimation = animation,
            .animations = getPlayerProjAnimations(),
            .zIndex = PROJECTILE_ZINDEX
        },
        .projectile = component::Projectile{
            .damage = damage,
            .isPlayerProjectile = true
        }
    };
}
}
