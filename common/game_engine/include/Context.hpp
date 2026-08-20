/*
** EPITECH PROJECT, 2024
** Rtype [WSL: Ubuntu]
** File description:
** IContext
*/

#pragma once

#include "IGraphicWrapper.hpp"
#include <memory>

struct Context {
    double deltaTimeSeconds = 0.0F;
    std::shared_ptr<IGraphicWrapper> graphicWrapper;
};
