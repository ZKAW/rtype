/*
** EPITECH PROJECT, 2024
** Rtype [WSL: Ubuntu]
** File description:
** drawHitbox
*/

#pragma once

#include "containers/zipper/Zipper.hpp"
#include "containers/SparseArray.hpp"
#include "ecs/Registry.hpp"
#include "ecs/components/allComponents.hpp"

#include "Context.hpp"
#include "IGraphicWrapper.hpp"
#include <SDL2/SDL.h>

class DrawHitbox {
public:
    void operator()(Registry &r) {
        SparseArray<component::Position> &positions = r.getComponents<component::Position>();
        SparseArray<component::Collidable> &collisions = r.getComponents<component::Collidable>();
        Context &context = r.getContext<Context>();
        std::shared_ptr<IGraphicWrapper> graphic = context.graphicWrapper;

        for (auto &&[pos, collision] : Zipper(positions, collisions)) {
            SDL_Rect rect = {(int)pos.x, (int)pos.y, (int)collision.w, (int)collision.h};
            std::shared_ptr<SDL_Renderer> renderer = getRenderer(graphic);
            SDL_SetRenderDrawColor(renderer.get(), 255, 0, 0, 255);
            SDL_RenderDrawRect(renderer.get(), &rect);
        }
    }

private:
    std::shared_ptr<SDL_Renderer> getRenderer(std::shared_ptr<IGraphicWrapper> &graphic) {
        std::any rendererAny = graphic->getWindow();
        return std::any_cast<std::shared_ptr<SDL_Renderer>>(rendererAny);
    }
};
