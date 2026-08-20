/*
** EPITECH PROJECT, 2024
** rtype4
** File description:
** LobbyServer
*/

#pragma once

#include <enet/enet.h>
#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <list>
#include <memory>
#include "ThreadPool.hpp"
#include "GameServer.hpp"
#include "LobbyManager.hpp"

class LobbyServer {
    public:
        LobbyServer(uint16_t port, uint16_t baseGamePort)
            : _network(port, 1000), _lobbyManager(baseGamePort) {}

        void run();

    private:
        void handleNewConnection(ENetPeer* peer);

    private:
        NetworkManager _network;
        LobbyManager _lobbyManager;
        std::atomic<bool> _running{true};
};
