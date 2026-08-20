/*
** EPITECH PROJECT, 2024
** Arcade [WSL: Ubuntu]
** File description:
** SurfaceLoader
*/

#pragma once

#include <SDL2/SDL_image.h>
#include <map>
#include <filesystem>

namespace sdl {
    class SurfaceLoaderError : public std::exception {
    public:
        SurfaceLoaderError(const std::string& message) : msg(message) {}
        const char* what() const noexcept override {
            return msg.c_str();
        }
    private:
        std::string msg;
    };

    class SurfaceLoader {
    public:
        SurfaceLoader() = default;
        ~SurfaceLoader() = default;

        std::shared_ptr<SDL_Surface> getSurface(const std::filesystem::path &path) {
            auto it = _dic.find(path);
            if (it == _dic.end())
                addSurface(path);
            return _dic[path];
        }

    private:
        void addSurface(const std::filesystem::path& path) {
            SDL_Surface *surface = IMG_Load(path.string().c_str());
            if (!surface)
                throw SurfaceLoaderError("Texture creation error: " + std::string(SDL_GetError()));
            _dic[path] = std::shared_ptr<SDL_Surface>(surface, SDL_FreeSurface);
        }

    private:
        std::map<std::filesystem::path, std::shared_ptr<SDL_Surface>> _dic;
    };
}
