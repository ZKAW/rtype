/*
** EPITECH PROJECT, 2024
** Rtype [WSL: Ubuntu]
** File description:
** IMediator
*/

#pragma once

class IMediator {
public:
    virtual ~IMediator() = default;
    virtual void notify() const = 0;
};
