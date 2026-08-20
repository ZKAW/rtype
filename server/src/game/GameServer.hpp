/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** GameServer
*/

#pragma once

#include "AGameCore.hpp"
#include "Network.hpp"
#include "ecs/components/allComponents.hpp"
#include "entity/allEntities.hpp"
#include "ecs/Registry.hpp"
#include <enet/enet.h>
#include <atomic>
#include <iostream>
#include <thread>
#include <mutex>
#include <cstring>
#include <list>
#include <utility>

#define DELTA_UPDATE_MS 50
#define SNAPSHOT_UPDATE_MS 500
#define MAX_CLIENTS 4

class GameClientError : public std::exception {
    public:
        explicit GameClientError(std::string message) : _message(std::move(message)) {};
        const char *what() const noexcept override { return _message.c_str(); }

    private:
        std::string _message;
};

class GameServer : public AGameCore {
    public:
        GameServer(const uint16_t &port, const size_t &maxClients);
        ~GameServer() override = default;

        void init() override;
        void update() override;
        void handleEvents() override;
        bool shouldTerminate() override;

        void onConnect(ENetEvent &event) override;
        void onDisconnect(ENetEvent &event) override;
        void onReceive(ENetEvent &event) override;

        bool isFull() const;
        uint16_t getPlayerAmount() const;
        uint16_t getPort() const;

    private:
        void sendSnapshotLoop();
        void sendDeltaUpdateLoop();
        void sendHandshake(ENetPeer* peer); // Will be moved onto on_connect
        void notifyConnection(const uint16_t &clientId);

        void handleEventsEvent(ENetPeer *peer, const fbs::InputEventPacket *packet);
        void changeDifficulty(float ratio);

    private:
        NetworkManager _network;
        std::list<ENetPeer*> _clients;
        uint16_t _connected_players = 0; // NOTE: could use ENET
        std::atomic<bool> _full{false};
};
