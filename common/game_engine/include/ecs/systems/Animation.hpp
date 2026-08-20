/*
** EPITECH PROJECT, 2024
** Rtype [WSL: Ubuntu]
** File description:
** sysdrawable
*/

#pragma once

#include "ecs/Registry.hpp"
#include "ecs/components/allComponents.hpp"
#include "containers/zipper/Zipper.hpp"
#include "Context.hpp"

namespace fsystem {
    class AnimationError : public std::exception {
    public:
        explicit AnimationError(const std::string &message) : _message(message) {}
        const char* what() const noexcept override { return _message.c_str();}
    private:
        std::string _message;
    };

    class Animation {
    public:
        void operator()(Registry &r, SparseArray<component::Drawable> &drawables) const {
            Context &context = r.getContext<Context>();

            for (auto &&[draw] : Zipper(drawables)) {
                std::string prev = draw.currentAnimation;
                draw.currentAnimation = draw.nextAnimation;
                component::Animation &anim = getAnimation(draw);
                if (prev != draw.currentAnimation)
                    resetAnimation(anim);
                updateAnimation(anim, context.deltaTimeSeconds);
            }
        }

    private:
        void advanceFrameLoop(component::Animation &anim) const {
            anim.currentFrame = (anim.currentFrame + 1) % anim.frameCount;
        }

        void advanceFrameNoLoop(component::Animation &anim) const {
            if (anim.currentFrame < anim.frameCount - 1)
                anim.currentFrame++;
        }

        void updateAnimation(component::Animation &anim, double deltaTimeSeconds) const {
            int reverse;

            anim.elapsedTime += deltaTimeSeconds;
            if (anim.elapsedTime >= anim.frameDuration) {
                reverse = (anim.leftToRight) ? 1 : -1;
                anim.elapsedTime = 0.0F;
                (anim.loop) ? advanceFrameLoop(anim) : advanceFrameNoLoop(anim);
                anim.srcRect.x = anim.xOrigin + (anim.currentFrame * anim.frameWidth * reverse);
            }
        }

        void resetAnimation(component::Animation &anim) const {
            anim.currentFrame = 0;
            anim.elapsedTime = 0.0F;
            anim.srcRect.x = anim.xOrigin;
        }

        component::Animation &getAnimation(component::Drawable &draw) const {
            auto it = draw.animations.find(draw.currentAnimation);
            if (it == draw.animations.end())
                throw AnimationError("No animation found for \"" + draw.currentAnimation + "\"");
            return it->second;
        }
    };
}