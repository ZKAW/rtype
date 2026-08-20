/*
** EPITECH PROJECT, 2024
** Arcade [WSL: Ubuntu]
** File description:
** TextureLoader
*/

#pragma once

#include "SurfaceLoader.hpp"
#include <filesystem>

namespace sdl {
    class TextureLoaderError : public std::exception {
    public:
        TextureLoaderError(const std::string& message) : msg(message) {}
        const char* what() const noexcept override {
            return msg.c_str();
        }
    private:
        std::string msg;
    };

    class TextureLoader {
    public:
        TextureLoader() : _renderer(nullptr) {};
        TextureLoader(std::shared_ptr<SDL_Renderer> _renderer) : _renderer(_renderer) {};
        ~TextureLoader()  = default;

        std::shared_ptr<SDL_Texture> getTexture(const std::filesystem::path& path) {
            auto it = _dic.find(path);
            if (it == _dic.end())
                addTexture(path);
            return _dic[path];
        }

    private:
        void addTexture(const std::filesystem::path& path) {
            if (!_renderer)
                throw TextureLoaderError("Renderer not set");
            std::shared_ptr<SDL_Surface> surface = _surfaceLoader.getSurface(path);
            if (!surface) {
                throw TextureLoaderError("Failed to load surface: " + path.string());
            }
            SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer.get(), surface.get());
            if (!texture) {
                throw TextureLoaderError("Texture creation error for " + path.string() + ": " + SDL_GetError());
            }
            _dic[path] = std::shared_ptr<SDL_Texture>(texture, SDL_DestroyTexture);
        }

    private:
        std::shared_ptr<SDL_Renderer> _renderer;
        SurfaceLoader _surfaceLoader;
        std::map<std::filesystem::path, std::shared_ptr<SDL_Texture>> _dic;
    };
}

