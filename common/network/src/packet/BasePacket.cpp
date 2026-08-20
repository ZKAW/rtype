/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** BasePacket
*/

#include "packet/PacketType.hpp"

auto operator<<(std::ostream& out, const PacketType& type) -> std::ostream&
{
    switch (type) {
        case PacketType::HANDSHAKE:
            out << "HANDSHAKE";
            break;
        case PacketType::CONNECT:
            out << "CONNECT";
            break;
        case PacketType::DISCONNECT:
            out << "DISCONNECT";
            break;
        case PacketType::PLAYER_ACTION:
            out << "PLAYER_ACTION";
            break;
        case PacketType::TICK:
            out << "TICK";
            break;
        case PacketType::SNAPSHOT:
            out << "SNAPSHOT";
            break;
        case PacketType::PLAYER_POS:
            out << "PLAYER_POS";
            break;
        case PacketType::PLAYER_PROJECTILE:
            out << "PLAYER_PROJECTILE";
            break;
        default:
            out << "UNKNOWN";
            break;
    }
    return out;
}
