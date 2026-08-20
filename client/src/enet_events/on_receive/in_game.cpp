/*
** EPITECH PROJECT, 2024
** Visual Studio Live Share (Workspace)
** File description:
** lobby
*/

#include "GameClient.hpp"
#include "packet/SnapshotPacket.hpp"

void GameClient::handlePlayerConnect(const fbs::ConnectPacket *packet) const
{
    if (!packet) {
        std::cerr << "Invalid connect packet received." << std::endl;
        return;
    }
    const uint32_t &connected_id = packet->uid();
    if (connected_id == _client_id) {
        std::cerr << "Skipping self connection" << std::endl;
        return;
    }
    std::cout << "New player connected with UID: " << connected_id << std::endl;
}

void GameClient::handlePlayerDisconnect(const fbs::DisconnectPacket *packet) const
{
    if (!packet) {
        std::cerr << "Invalid disconnect packet received." << std::endl;
        return;
    }
    const uint32_t &disconnected_id = packet->uid();
    if (disconnected_id == _client_id) {
        std::cerr << "Skipping self disconnection" << std::endl;
        return;
    }
    std::cout << "Player disconnected with UID: " << disconnected_id << std::endl;
}

void GameClient::handleSnapshot(const fbs::SnapshotPacket *packet)
{
    if (!packet) {
        std::cerr << "Invalid snapshot packet received." << std::endl;
        return;
    }
    auto snapshot = SnapshotPacket::unpack(packet);
    std::cout << "Received snapshot packet from server." << std::endl;

    // clear existing components
    _registry.getComponents<component::Position>().clear();
    _registry.getComponents<component::Drawable>().clear();

    // set new components
    _registry.getComponents<component::Position>() = snapshot->positions;
    _registry.getComponents<component::Drawable>() = snapshot->drawables;


    // // log all positions
    // for (auto &&[id, position] : IndexedZipper(_registry.getComponents<component::Position>())) {
    //     std::cout << "Position of entity " << id << ": " << position.x << ", " << position.y << std::endl;
    // }
    // // log all drawables
    // for (auto &&[id, drawable] : IndexedZipper(_registry.getComponents<component::Drawable>())) {
    //     std::cout << "Drawable of entity " << id << ": " << drawable.currentAnimation << std::endl;
    // }
    // std::cout << "Received snapshot packet from server." << std::endl;
}

void GameClient::onReceiveInGame(ENetEvent &event)
{
    const auto packet_info = PacketHelper::getPacketInfo(event.packet);
    switch (packet_info.type) {
        case fbs::PacketType::PacketType_CONNECT:
            if (const auto *packet = PacketHelper::getPacketData<fbs::ConnectPacket>(packet_info)) {
                handlePlayerConnect(packet);
            }
            break;
        case fbs::PacketType::PacketType_DISCONNECT:
            if (const auto *packet = PacketHelper::getPacketData<fbs::DisconnectPacket>(packet_info)) {
                handlePlayerDisconnect(packet);
            }
            break;
        case fbs::PacketType::PacketType_SNAPSHOT:
            // std::cout << "Received snapshot packet from server." << std::endl;
            if (const auto *packet = PacketHelper::getPacketData<fbs::SnapshotPacket>(packet_info)) {
                handleSnapshot(packet);
            }
            break;
        default:
            std::cerr << "Received unknown packet type" << std::endl;
            break;
    }
}