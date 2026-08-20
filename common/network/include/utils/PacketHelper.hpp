/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** PacketHelper
*/

#pragma once
#include <cstdint>
#include <enet/enet.h>
#include <lz4.h>

#include "BitPacking.hpp"
#include "packet_types_generated.h"

class PacketHelper {
public:
    struct PacketInfo {
        const uint8_t* data;
        size_t size;
        fbs::PacketType type;
    };

    static PacketInfo getPacketInfo(const ENetPacket* packet) {
        if (!packet || packet->dataLength < sizeof(uint32_t)) {
            return {nullptr, 0, fbs::PacketType::PacketType_NONE};
        }

        uint32_t header;
        memcpy(&header, packet->data, sizeof(header));
        auto [original_size, type] = BitPacking::unpackHeader(header);
        auto* decompressed_buffer = new uint8_t[original_size];

        int decompressed_size = LZ4_decompress_safe(
            reinterpret_cast<const char*>(packet->data + sizeof(header)),
            reinterpret_cast<char*>(decompressed_buffer),
            packet->dataLength - sizeof(header),
            original_size
        );

        if (decompressed_size <= 0) {
            delete[] decompressed_buffer;
            return {nullptr, 0, fbs::PacketType::PacketType_NONE};
        }

        return {
            decompressed_buffer,
            static_cast<size_t>(decompressed_size),
            static_cast<fbs::PacketType>(type)
        };
    }

    template<typename T>
    static const T* getPacketData(const PacketInfo& info) {
        if (!info.data) return nullptr;

        flatbuffers::Verifier verifier(info.data, info.size);
        if (!verifier.VerifyBuffer<T>()) {
            return nullptr;
        }
        return flatbuffers::GetRoot<T>(info.data);
    }
};
