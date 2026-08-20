/*
** EPITECH PROJECT, 2024
** Arcade [WSL: Ubuntu]
** File description:
** FontLoader
*/

#pragma once

#include <map>
#include <filesystem>
#include <SDL2/SDL_ttf.h>

namespace sdl {
    class FontLoaderError : public std::exception {
    public:
        FontLoaderError(const std::string& message) : msg(message) {}
        const char* what() const noexcept override {
            return msg.c_str();
        }
    private:
        std::string msg;
    };

    class FontLoader {
    public:
        FontLoader() = default;
        ~FontLoader() = default;

        std::shared_ptr<TTF_Font> getFont(const std::filesystem::path &path, int size) {
            auto it = _dic.find(std::make_pair(path, size));
            if (it == _dic.end())
                addFont(path, size);
            return it->second;
        }

    private:
        void addFont(const std::filesystem::path &path, int size) {
            TTF_Font *font = TTF_OpenFont(path.string().c_str(), size);
            if (!font)
                throw FontLoaderError("TTF_OpenFont failed : " + std::string(TTF_GetError()));
            _dic[std::make_pair(path, size)] = std::shared_ptr<TTF_Font>(font, TTF_CloseFont);
        }

    private:
        std::map<std::pair<std::filesystem::path, int>, std::shared_ptr<TTF_Font>> _dic;
    };
}
