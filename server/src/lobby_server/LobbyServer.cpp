/*
** EPITECH PROJECT, 2024
** rtype4
** File description:
** LobbyServer
*/

#include "LobbyServer.hpp"

void LobbyServer::run() {
    while (_running) {
        ENetEvent event;
        while (enet_host_service(_network.getHost().get(), &event, 0) > 0) {
            if (event.type == ENET_EVENT_TYPE_CONNECT) {
                handleNewConnection(event.peer);
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}
