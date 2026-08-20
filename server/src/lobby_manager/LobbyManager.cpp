/*
** EPITECH PROJECT, 2024
** rtype4
** File description:
** LobbyManager
*/

#include "LobbyManager.hpp"

LobbyManager::LobbyManager(uint16_t basePort)
    : _basePort(basePort), _threadPool(MAX_THREADS) {}

LobbyManager::~LobbyManager() {
    std::lock_guard<std::mutex> lock(_lobbiesMutex);
    _lobbies.clear();
}

uint16_t LobbyManager::createLobby() {
    std::cout << "Creating new lobby..." << std::endl;
    uint16_t port;
    {
        std::lock_guard<std::mutex> lock(_lobbiesMutex);
        port = _basePort + _lobbies.size();
    }

    // auto lobby = std::make_shared<Lobby>(port);
    std::cout << "Initializing new lobby..." << std::endl;
    auto lobby = std::make_shared<GameServer>(port, MAX_CLIENTS);

    _threadPool.enqueue([lobby] {
        lobby->init();
        std::cout << "Running new lobby..." << std::endl;
        lobby->run();
    });
    std::cout << "Enqueued lobby on port " << port << std::endl;
    {
        std::lock_guard<std::mutex> lock(_lobbiesMutex);
        _lobbies.push_back(lobby);
    }
    std::cout << "New lobby created on port " << port << std::endl;
    return port;
}

uint16_t LobbyManager::findAvailableLobby() {
    std::cout << "Finding available lobby..." << std::endl;
    {
        std::lock_guard<std::mutex> lock(_lobbiesMutex);

        // Find existing lobby with space
        for (const auto& lobby : _lobbies) {
            if (!lobby->shouldTerminate() && lobby->getPlayerAmount() < MAX_CLIENTS) {
                std::cout << "Found available lobby on port " << lobby->getPort() << std::endl;
                return lobby->getPort();
            }
        }
    }
    std::cout << "No available lobby found. Creating new lobby..." << std::endl;
    return createLobby();
}

void LobbyManager::removeLobby(uint16_t port) {
    std::lock_guard<std::mutex> lock(_lobbiesMutex);
    _lobbies.remove_if([port](const auto& lobby) {
        return lobby->getPort() == port;
    });
}