/*
** EPITECH PROJECT, 2024
** Rtype [WSL: Ubuntu]
** File description:
** DrawSystem
*/

#pragma once

#include "ecs/Registry.hpp"
#include "ecs/components/allComponents.hpp"
#include "Context.hpp"
#include "IGraphicWrapper.hpp"
#include "containers/zipper/Zipper.hpp"
#include <SDL2/SDL.h>
#include <vector>
#include <algorithm>

#define MAX_OPACITY 255

class DrawableError : public std::exception {
public:
    explicit DrawableError(const std::string &message) : _message(message) {}
    const char* what() const noexcept override { return _message.c_str();}
private:
    std::string _message;
};

// Pas opti !!!!!!
// stocker le sort et update si changement de zindex

class DrawSystem {
public:
    void operator()(Registry &r, std::shared_ptr<IGraphicWrapper> &graphic ,std::shared_ptr<SDL_Renderer> &renderer) {
        SparseArray<component::Position> &positions = r.getComponents<component::Position>();
        SparseArray<component::Drawable> &drawables = r.getComponents<component::Drawable>();
        static float score = 0;

        setRenderQueue(positions, drawables);

        // std::cout << "Render queue size: " << _renderQueue.size() << std::endl;

        score+= 0.1;
        for (auto &&[pos, draw] : _renderQueue) {
            component::Animation &anim = getCurrentAnimation(draw);
            //std::cout << "text=" << anim.texture << std::endl;

            std::shared_ptr<SDL_Texture> texture = getTexture(anim.texture, graphic);
            SDL_Rect srcRect = RectToSDLRect(anim.srcRect);
            SDL_Rect destRect = RectToSDLRect(anim.destRect);
            destRect.x = pos.x;
            destRect.y = pos.y;
            // std::cout << "Rendering texture: " << anim.texture << " at position: " << pos.x << ", " << pos.y << std::endl;
            if (SDL_RenderCopy(renderer.get(), texture.get(), &srcRect, &destRect) != 0) {
                std::cerr << "SDL_RenderCopy failed: " << SDL_GetError() << std::endl;
            }
            if (anim.texture == BACKGROUND_IMAGE) {
                displayScore(renderer, score);
            }
            if (anim.texture == DEATH_IMAGE) {
                score += 1;
            }
        }
    }

private:
    component::Animation &getCurrentAnimation(component::Drawable &draw) const {
        auto it = draw.animations.find(draw.currentAnimation);
        if (it == draw.animations.end())
            throw DrawableError("No animation found for \"" + draw.currentAnimation + "\"");
        return it->second;
    }

    void setRenderQueue(SparseArray<component::Position> &positions, SparseArray<component::Drawable> &drawables) {
        _renderQueue.clear();

        for (auto &&[pos, draw] : Zipper(positions, drawables))
            _renderQueue.emplace_back(pos, draw);

        std::sort(_renderQueue.begin(), _renderQueue.end(), [](const auto &a, const auto &b) {
            return std::get<1>(a).zIndex < std::get<1>(b).zIndex;
        });
    }

    std::shared_ptr<SDL_Texture> getTexture(const std::string &path, std::shared_ptr<IGraphicWrapper> &graphic) {
        std::any textureAny = graphic->createTexture(path);
        return std::any_cast<std::shared_ptr<SDL_Texture>>(textureAny);
    }

    SDL_Rect RectToSDLRect(const component::Rect &rect) {
        return SDL_Rect{rect.x, rect.y, rect.w, rect.h};
    }

    void displayScore(std::shared_ptr<SDL_Renderer> &renderer, float score)
    {
        static SDL_Color white = {255, 255, 255};
        static TTF_Font* font = TTF_OpenFont("client/font/aadhunik.ttf", 24);
        static SDL_Rect rmsg = { 10, 10, 100, 50};
        std::string text = "Score : " + std::to_string((int) score);

        SDL_Surface* smsg = TTF_RenderText_Solid(font, text.c_str(), white);
        SDL_Texture* msg = SDL_CreateTextureFromSurface(renderer.get(), smsg);
        SDL_RenderCopy(renderer.get(), msg, nullptr, &rmsg);
        SDL_FreeSurface(smsg);
        SDL_DestroyTexture(msg);
        //SDL_SetWindowTitle(SDL_GL_GetCurrentWindow(), ctext);
    }

private:
    std::vector<std::tuple<component::Position, component::Drawable>> _renderQueue;
};
