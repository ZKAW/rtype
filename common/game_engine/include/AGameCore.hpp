/*
** EPITECH PROJECT, 2024
** src
** File description:
** Core
*/

#pragma once

#include "IGameCore.hpp"
#include "IGraphicWrapper.hpp"
#include "Context.hpp"
#include <iostream>
#include <string>
#include "ecs/Registry.hpp"
#include "ecs/systems/allSystems.hpp"
#include "ecs/components/allComponents.hpp"
#include "entity/allEntities.hpp"
#include "Context.hpp"
#include "cross_attributes.hpp"

#define UNDEFINED_CLIENT_ID 0xFFFF
#define NANOSECONDS_PER_SECOND 1e9

class AGameCore : public IGameCore {
    public:
        AGameCore(std::shared_ptr<IGraphicWrapper> graphicWrapper = nullptr);
        ~AGameCore() = default;

        // Game loop
        virtual void init() = 0;
        virtual void update() = 0;
        virtual void run() override;
        virtual void handleEvents() override {};
        virtual void render() override {};
        virtual bool shouldTerminate() override { return false; };

        // Context
        virtual void initContext() override;
        virtual void updateContext(double delta) override;

        // Network
        virtual void onConnect(ENetEvent &event) = 0;
        virtual void onDisconnect(ENetEvent &event) = 0;
        virtual void onReceive(ENetEvent &event) = 0;

    private:
        void registerComponents();
        void registerSystem();
        void registerBuilders();

    protected:
        const int _FPS = 60;
        bool _running = true;
        Registry _registry;
        uint32_t _currentTick = 0;
        std::shared_ptr<IGraphicWrapper> _graphicWrapper;

    private:
        std::unordered_map<std::type_index, std::function<Entity(std::any)>> _builders;
};
