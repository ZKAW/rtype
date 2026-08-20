/*
** EPITECH PROJECT, 2024
** Visual Studio Live Share (Workspace)
** File description:
** lobby
*/

#include "GameClient.hpp"

void GameClient::handleHandshake(const fbs::HandshakePacket *packet)
{
    if (!packet) return;

    _client_id = packet->uid();
    _width = packet->window_width();
    _height = packet->window_height();
    _currentTick = packet->tick();

    std::cout << "Received handshake packet" << std::endl;
    std::cout << "Client id: " << _client_id << std::endl;
    std::cout << "Window width: " << _width << std::endl;
    std::cout << "Window height: " << _height << std::endl;
}

void GameClient::handleRedirect(const fbs::RedirectPacket* packet) {
    // Disconnect from current server
    std::cout << "Received redirect packet from server. Redirecting to new server." << std::endl;

    char ip[INET_ADDRSTRLEN];
    std::string original_host = enet_address_get_host_ip(&_peer->address, ip, sizeof(ip)) == 0 ? 
                            std::string(ip) : "127.0.0.1";

    cleanupHost();
    _network.setHost(original_host, packet->port());

    uint16_t new_port = packet->port();
    connect();
    std::cout << "Redirected to new server at " << ip << ":" << new_port << std::endl;
    std::cout << "Redirect completed with new server." << std::endl;
}

void GameClient::onReceiveInLobby(ENetEvent &event)
{
    if (!event.packet) {
        std::cerr << "Received null packet in lobby" << std::endl;
        return;
    }

    std::cout << "Processing lobby packet" << std::endl;
    auto packet_info = PacketHelper::getPacketInfo(event.packet);
    std::cout << "Packet type: " << static_cast<int>(packet_info.type) << std::endl;

    switch (packet_info.type) {
        case fbs::PacketType::PacketType_REDIRECT:
            if (const auto *packet = PacketHelper::getPacketData<fbs::RedirectPacket>(packet_info)) {
                handleRedirect(packet);
            }
            break;
        case fbs::PacketType::PacketType_HANDSHAKE:
            if (const auto *packet = PacketHelper::getPacketData<fbs::HandshakePacket>(packet_info)) {
                handleHandshake(packet);
                _state = ClientState::IN_GAME;
            }
            break;
        default:
            std::cerr << "Received unknown packet type in lobby" << std::endl;
            break;
    }

    enet_packet_destroy(event.packet);
}
