/*
** EPITECH PROJECT, 2024
** rtype4
** File description:
** on_connect
*/

#include "../LobbyServer.hpp"

void LobbyServer::handleNewConnection(ENetPeer* peer) {
    std::cout << "New connection received on lobby (peer id: " << peer->incomingPeerID << ")" << std::endl;
    uint16_t port = _lobbyManager.findAvailableLobby();

    // Send redirect packet to client
    std::cout << "Redirecting client to new server on port " << port << std::endl;
    flatbuffers::FlatBufferBuilder builder;
    auto redirect = fbs::CreateRedirectPacket(builder, port);
    _network.send<fbs::RedirectPacket>(peer, builder, redirect,
        fbs::PacketType::PacketType_REDIRECT);
    std::cout << "Redirect packet sent to client" << std::endl;
    // disconnect client from lobby
    // enet_peer_disconnect_now(peer, 0);
}