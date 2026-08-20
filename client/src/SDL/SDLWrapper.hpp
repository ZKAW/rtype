/*
** EPITECH PROJECT, 2024
** Rtype [WSL: Ubuntu]
** File description:
** SDLWrapper
*/

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <stdexcept>
#include <memory>
#include <map>
#include <list>
#include "IGraphicWrapper.hpp"
#include "InputQueue.hpp"
#include "TextureLoader.hpp"
#include "SurfaceLoader.hpp"
#include "FontLoader.hpp"

#define WINDOW_FLAGS SDL_WINDOW_SHOWN
constexpr float kMillisecondsToSeconds = 1000.0F;

namespace sdl {
    class SDLWrapperError : public std::exception {
    public:
        SDLWrapperError(const std::string& message) : msg(message) {}
        const char* what() const noexcept override {
            return msg.c_str();
        }
    private:
        std::string msg;
    };

    class SDLWrapper : public IGraphicWrapper {
    public:
        SDLWrapper();
        ~SDLWrapper() override;

        void createWindow(const std::string& title, int width, int height) override;

        // std::any = shared_ptr<SDL_Window>
        std::any getWindow() const override;

        // std::any = shared_ptr<SDL_Texture>
        std::any createTexture(const std::string& path) override;

        // std::any = std::shared_ptr<TTF_Font>
        std::any createFont(const std::string& path, int size) override;

        std::list<InputEvent> getInputEvents() override;

        // std::any = SDL_Keycode
        InputKey keyToInputKey(std::any keycode) override;

        WindowSize getWindowSize() override;

    private:
        std::shared_ptr<SDL_Window> _window;
        std::shared_ptr<SDL_Renderer> _renderer;
        TextureLoader _textureLoader;
        SurfaceLoader _surfaceLoader;
        FontLoader _fontLoader;

        static const std::map<SDL_Keycode, InputKey> _keymap;
    };
} // namespace sdl
