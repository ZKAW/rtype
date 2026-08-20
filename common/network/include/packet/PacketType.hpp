/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** PacketType
*/

#pragma once

#include <cstdint>
#include <iostream>

enum class PacketType : uint8_t {
    UNKNOWN = 0x00,

    // Common
    HANDSHAKE = 0x01,
    DISCONNECT = 0x02, // TODO: create packettype for this: it will be used to notify clients of disconnection of a peer
    CONNECT = 0x03, // TODO: create packettype for this: it will be used to notify clients of connection of a peer

    // Client -> Server
    PLAYER_ACTION = 0x04, // Sent by client to server
    INPUT_EVENT = 0x05, // Sent by client to server

    // Server -> Client
    TICK = 0x06, // NOTE: Should be considered as tick can be sent through HANDSHAKE
    SNAPSHOT = 0x07,

    PLAYER_POS = 0x08, // Sent from server and dispatched to clients
    PLAYER_PROJECTILE = 0x09,

    ENEMY_POS = 0x0A,
    ENEMY_PROJECTILE = 0x0B,
};

auto operator<<(std::ostream& out, const PacketType& type) -> std::ostream&;
