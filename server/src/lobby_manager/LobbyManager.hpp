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

#define MAX_THREADS 4

class LobbyManager {

    public:
        explicit LobbyManager(uint16_t basePort);
        ~LobbyManager();

    public:
        uint16_t createLobby();
        uint16_t findAvailableLobby();
        void removeLobby(uint16_t port);

    private:

    private:
        std::list<std::shared_ptr<GameServer>> _lobbies;
        std::mutex _lobbiesMutex;
        uint16_t _basePort;
        ThreadPool _threadPool;
};