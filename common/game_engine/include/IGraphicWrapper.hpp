/*
** EPITECH PROJECT, 2024
** Rtype [WSL: Ubuntu]
** File description:
** SDLWrapper
*/

#pragma once

#include <string>
#include <any>
#include "InputQueue.hpp"
#include <list>

struct WindowSize {
    int width;
    int height;
};

class IGraphicWrapper {
public:
    virtual ~IGraphicWrapper() = default;

    virtual void createWindow(const std::string& title, int width, int height) = 0;
    virtual std::any getWindow() const = 0;
    virtual std::any createTexture(const std::string& path) = 0;
    virtual std::any createFont(const std::string& path, int size) = 0;
    virtual std::list<InputEvent> getInputEvents() = 0;
    virtual InputKey keyToInputKey(std::any key) = 0;
    virtual WindowSize getWindowSize() = 0;
};
