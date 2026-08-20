/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** on_connect
*/

#include "GameServer.hpp"

void GameServer::notifyConnection(const uint16_t &clientId)
{
    flatbuffers::FlatBufferBuilder builder;
    auto connect_packet = fbs::CreateConnectPacket(
        builder,
        clientId
    );

    _network.broadcast<fbs::ConnectPacket>(builder, connect_packet, fbs::PacketType::PacketType_CONNECT);
    std::cout << "Notified all clients of new connection with UID: " << clientId << std::endl;
}

void GameServer::sendHandshake(ENetPeer *peer) {
    flatbuffers::FlatBufferBuilder builder;
    auto handshake_packet = fbs::CreateHandshakePacket(
        builder,
        peer->incomingPeerID,
        _currentTick,
        WINDOW_WIDTH,
        WINDOW_HEIGHT
    );
    _network.send<fbs::HandshakePacket>(peer, builder, handshake_packet, fbs::PacketType::PacketType_HANDSHAKE);
    std::cout << "Sent handshake packet to client with UID: " << peer->incomingPeerID << std::endl;
}

void GameServer::onConnect(ENetEvent &event) {
    if (isFull()) {
        // Reject connection if lobby is full
        enet_peer_disconnect_now(event.peer, 0);
        return;
    }

    // Existing connection logic
    std::cout << "A new client connected" << std::endl;
    // start chrome
    sendHandshake(event.peer);

    _clients.push_back(event.peer);
    entity::Player joining_player = entity::getPlayer(event.peer->incomingPeerID);
    joining_player.position.x = 100;
    joining_player.position.y = 200;
    _registry.createEntity(joining_player);

    _connected_players++;
    notifyConnection(event.peer->incomingPeerID);

    if (isFull()) {
        _full = true;
    }
}
