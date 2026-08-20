/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** GameClient
*/

#pragma once

#include <iostream>
#include <enet/enet.h>
#include <iostream>
#include <thread>
#include <chrono>

#ifdef _WIN32
    #include <conio.h>
#else
    #include <termios.h>
    #include <fcntl.h>
    #include <unistd.h>
#endif

#include "AGameCore.hpp"
#include "SDL/SDLWrapper.hpp"
#include "Network.hpp"
#include "Context.hpp"
#include "InputQueue.hpp"

enum ClientState {
    WAITING_FOR_LOBBY,
    IN_GAME,
};

class GameClientError : public std::exception {
    public:
        GameClientError(const std::string &message) : _message(message) {};
        const char *what() const noexcept override { return _message.c_str(); }

    private:
        std::string _message;
};

class GameClient : public AGameCore {
    public:
        GameClient(const std::string &host, const uint16_t &port);
        ~GameClient();

        void init() override;
        void update() override {};
        void render() override;

        void handleEvents() override;

        auto shouldTerminate() -> bool override;

    protected:
        void onConnect(ENetEvent &event) override;
        void onDisconnect(ENetEvent &event) override;
        void onReceive(ENetEvent &event) override;

    private:

        // network
        void connect();
        void cleanupHost();
        void handlePacket();

        // custom enet_events
        void onReceiveInLobby(ENetEvent &event);
        void onReceiveInGame(ENetEvent &event);

        // packet handlers
        void handleHandshake(const fbs::HandshakePacket *packet);
        void handlePlayerConnect(const fbs::ConnectPacket *packet) const;
        void handlePlayerDisconnect(const fbs::DisconnectPacket *packet) const;
        void handleSnapshot(const fbs::SnapshotPacket *packet);
        void handleRedirect(const fbs::RedirectPacket *packet);

    private:
        NetworkManager _network;

        ENetPeer *_peer;
        uint16_t _client_id = UNDEFINED_CLIENT_ID;
        int _width = 0;
        int _height = 0;
        ClientState _state = WAITING_FOR_LOBBY;

        static constexpr int HANDSHAKE_TIMEOUT_MS = 5000;
        static constexpr int DISCONNECT_TIMEOUT_MS = 1000;
};
