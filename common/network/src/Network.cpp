/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Network
*/

#include "Network.hpp"
#include <iostream>

namespace {
    std::shared_ptr<ENetHost> createHost(const std::shared_ptr<ENetAddress>& address, size_t maxClients)
    {
        ENetHost *host = enet_host_create(address.get(), maxClients, 2, 0, 0);
        if (!host) {
            enet_deinitialize();
            throw NetworkManagerError("An error occurred while creating the server host");
        }
        return std::shared_ptr<ENetHost>(host, enet_host_destroy);
    }
}

// Constructor for server
NetworkManager::NetworkManager(const uint16_t &port, const size_t &maxClients = 1)
{
    if (enet_initialize() != 0)
        throw NetworkManagerError("An error occurred while initializing ENet");

    _address = std::make_shared<ENetAddress>();
    _address->host = ENET_HOST_ANY; // Listen on all interfaces
    _address->port = port;

    _host = createHost(_address, maxClients);
}

// Constructor for client
NetworkManager::NetworkManager(const std::string &host, const uint16_t &port)
{
    if (enet_initialize() != 0)
        throw NetworkManagerError("An error occurred while initializing ENet");

    setHost(host, port);
}

void NetworkManager::setHost(const std::string &host, const uint16_t &port)
{
    _address = std::make_shared<ENetAddress>();
    _address->port = port;

    if (enet_address_set_host(_address.get(), host.c_str()) != 0)
        throw NetworkManagerError("An error occurred while setting the server host");

    _host = createHost(nullptr, 1); // No need to bind address for the client
}

NetworkManager::~NetworkManager()
{
    cleanupHost();
    enet_deinitialize();
}

void NetworkManager::sendPacket(const ENetPeer *peer, const ENetPacket *packet)
{
    enet_peer_send(const_cast<ENetPeer *>(peer), 0, const_cast<ENetPacket *>(packet));
    enet_host_flush(_host.get());
}

void NetworkManager::broadcastPacket(const ENetPacket *packet)
{
    enet_host_broadcast(_host.get(), 0, const_cast<ENetPacket *>(packet));
    enet_host_flush(_host.get());
}
