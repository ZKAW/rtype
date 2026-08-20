/*
** EPITECH PROJECT, 2024
** src
** File description:
** Core
*/

#pragma once

#include <stdexcept>
#include <enet/enet.h>

class GameCoreError : public std::exception {
public:
    explicit GameCoreError(const std::string &message) : _message(message) {}
    const char *what() const noexcept override { return _message.c_str(); }

private:
    std::string _message;
};


class IGameCore {
    public:
        virtual ~IGameCore() = default;

        // Game loop
        virtual void init() = 0;
        virtual void run() = 0;
        virtual void update() = 0;
        virtual void handleEvents() = 0;
        virtual void render() = 0;
        virtual bool shouldTerminate() = 0;

        // Context
        virtual void initContext() = 0;
        virtual void updateContext(double delta) = 0;

        // Network
        virtual void onConnect(ENetEvent &event) = 0;
        virtual void onDisconnect(ENetEvent &event) = 0;
        virtual void onReceive(ENetEvent &event) = 0;
};
