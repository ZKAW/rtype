/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** on_disconnect
*/

#include "GameServer.hpp"

void GameServer::onDisconnect(ENetEvent &event)
{
    std::cout << "Client with id " << event.peer->incomingPeerID << " disconnected" << std::endl;

    flatbuffers::FlatBufferBuilder builder;
    auto connect_packet = fbs::CreateDisconnectPacket(
        builder,
        event.peer->incomingPeerID
    );
    _network.broadcast<fbs::DisconnectPacket>(builder, connect_packet, fbs::PacketType::PacketType_DISCONNECT);

    for (auto &&[id, player] : IndexedZipper(_registry.getComponents<component::Player>())) {
        if (player.clientId == event.peer->incomingPeerID) {
            _registry.killEntity(id);
            break;
        }
    }

    float ratio = static_cast<float>(_connected_players - 1)/static_cast<float>(_connected_players);
    _connected_players--;
    changeDifficulty(ratio);
}
