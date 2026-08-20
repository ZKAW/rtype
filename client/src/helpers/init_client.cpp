/*
** EPITECH PROJECT, 2024
** Visual Studio Live Share (Workspace)
** File description:
** init_client
*/

#include "GameClient.hpp"

void GameClient::connect()
{
    std::cout << "Initializing ENet client on port " << _network.getPort() << std::endl;

    _peer = enet_host_connect(_network.getHost().get(), _network.getAddress().get(), 2, 0);
    if (!_peer) {
        cleanupHost();
        throw GameClientError("No available peers for connection.");
    }
}

void GameClient::cleanupHost()
{
    enet_peer_reset(_peer);
    _network.cleanupHost();
    enet_deinitialize();
}
