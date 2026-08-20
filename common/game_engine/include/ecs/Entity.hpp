/*
** EPITECH PROJECT, 2024
** Rtype [WSL: Ubuntu]
** File description:
** entity
*/

#pragma once

#include <stddef.h>

class Entity {
public:
    using type = size_t;
    operator size_t() const { return _id; }

private:
    explicit Entity(size_t id) : _id(id) {}
    size_t _id;

friend class Registry;
};
