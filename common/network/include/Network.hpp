/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Network
*/

#pragma once

#include <iostream>
#include <optional>
#include <memory>
#include <utility>
#include <enet/enet.h>
#include <flatbuffers/flatbuffers.h>
#include <lz4.h>

#include "packet_types_generated.h"
#include "utils/BitPacking.hpp"
#include "utils/PacketHelper.hpp"

class NetworkManagerError : public std::exception {
    public:
        explicit NetworkManagerError(std::string message) : _message(std::move(message)) {};
        const char *what() const noexcept override { return _message.c_str(); }

    private:
        std::string _message;
};

class NetworkManager {
    public:
        NetworkManager() = delete;
        NetworkManager(const uint16_t &port, const size_t &maxClients); // Server
        NetworkManager(const std::string &host, const uint16_t &port); // Client
        ~NetworkManager();

        void sendPacket(const ENetPeer *peer, const ENetPacket *packet);
        void broadcastPacket(const ENetPacket *packet);
        std::shared_ptr<ENetHost> getHost() const { return _host; }
        std::shared_ptr<ENetAddress> getAddress() const { return _address; }
        void setHost(const std::string &host, const uint16_t &port);
        uint16_t getPort() const { return _address->port; }

        void cleanupHost() { _host.reset(); }

    public:
        template<typename T>
        ENetPacket* createPacket(flatbuffers::FlatBufferBuilder& builder,
            const flatbuffers::Offset<T>& packet,
            fbs::PacketType type)
        {
            builder.Finish(packet);
            const uint8_t* buffer = builder.GetBufferPointer();
            const size_t size = builder.GetSize();

            uint32_t header = BitPacking::packHeader(size,
                static_cast<uint8_t>(type));

            const int max_dst_size = LZ4_compressBound(size);
            auto* compressed_buffer = new uint8_t[max_dst_size];

            int compressed_size = LZ4_compress_default(
                reinterpret_cast<const char*>(buffer),
                reinterpret_cast<char*>(compressed_buffer),
                size,
                max_dst_size
            );

            if (compressed_size <= 0) {
                delete[] compressed_buffer;
                return nullptr;
            }

            size_t total_size = sizeof(header) + compressed_size;
            auto* packet_buffer = new uint8_t[total_size];

            memcpy(packet_buffer, &header, sizeof(header));
            memcpy(packet_buffer + sizeof(header), compressed_buffer, compressed_size);

            delete[] compressed_buffer;

            return enet_packet_create(packet_buffer, total_size,
                ENET_PACKET_FLAG_RELIABLE | ENET_PACKET_FLAG_NO_ALLOCATE);
        }

        template<typename T>
        void send(ENetPeer* peer, flatbuffers::FlatBufferBuilder& builder,
            const flatbuffers::Offset<T>& packet, fbs::PacketType type)
        {
            if (ENetPacket* enet_packet = createPacket(builder, packet, type))
            {
                enet_peer_send(peer, 0, enet_packet);
                enet_host_flush(_host.get());
            }
        }

        template<typename T>
        void broadcast(flatbuffers::FlatBufferBuilder& builder,
            const flatbuffers::Offset<T>& packet, fbs::PacketType type)
        {
            if (!packet.o) {
                std::cerr << "Failed to create packet" << std::endl;
                return;
            }
            if (ENetPacket* enet_packet = createPacket(builder, packet, type))
            {
                enet_host_broadcast(_host.get(), 0, enet_packet);
                enet_host_flush(_host.get());
            }
        }


    private:
        std::shared_ptr<ENetHost> _host;
        std::shared_ptr<ENetAddress> _address;
};
