/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** GameServer
*/

#include "GameServer.hpp"
#include "packet/SnapshotPacket.hpp"
#include "entity/Background.hpp"

GameServer::GameServer(const uint16_t &port, const size_t &maxClients)
    : _network(port, maxClients)
{
    enet_host_bandwidth_limit(_network.getHost().get(), 0, 0);
    enet_peer_ping_interval(_network.getHost()->peers, 500);
    // enet_peer_timeout(_server->peers, 0, 30000, 30000);  // Set timeout for connection

    std::cout << "Server started on port " << port << "...\n";
}

void GameServer::init() {
    srand(static_cast<unsigned int>(time(nullptr)));
    _registry.createEntity(entity::getBackground(WINDOW_WIDTH, WINDOW_HEIGHT));
}

void GameServer::update() {
    static int nb = 1;
    unsigned int life_multiplier = _connected_players;

    if (life_multiplier == 0)
        life_multiplier = 1;

    if (rand() % SPAWN_RATE < nb) {
        _registry.createEntity(entity::getPataPata(WINDOW_WIDTH, 50 + (rand() % (WINDOW_HEIGHT - 150)), life_multiplier));
        _registry.createEntity(entity::getQuoicoubax(WINDOW_WIDTH, 50 + (rand() % (WINDOW_HEIGHT - 150)), life_multiplier));
    }
    if (_currentTick % WIPER_RATE == 0) {
        _registry.createEntity(entity::getWiper(rand() % WINDOW_WIDTH, 50 + (rand() % (WINDOW_HEIGHT - 150))));
    }
    if (_currentTick == BOSS_WAIT) {
        _registry.createEntity(entity::getBoss(static_cast<float>(BOSS_POS_X), static_cast<float>(BOSS_POS_Y), life_multiplier));
    }
    nb = nb + 0.001;

    _registry.runSystems();

    // send snapshot to all clients
    try {
        flatbuffers::FlatBufferBuilder builder;
        auto snap_packet = SnapshotPacket::create(
            builder,
            _registry.getComponents<component::Position>(),
            _registry.getComponents<component::Drawable>()
        );

        if (!snap_packet.o) {
            std::cerr << "Failed to create SnapshotPacket" << std::endl;
            return;
        }

        _network.broadcast<fbs::SnapshotPacket>(builder, snap_packet, fbs::PacketType::PacketType_SNAPSHOT);
    } catch (const std::exception &e) {
        std::cerr << "Exception in GameServer::update(): " << e.what() << std::endl;
    }
}

void GameServer::handleEvents() {
    ENetEvent event;
    while (enet_host_service(_network.getHost().get(), &event, 0) > 0) {
        switch (event.type) {
            case ENET_EVENT_TYPE_CONNECT:
                onConnect(event);
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                onDisconnect(event);
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                onReceive(event);
                break;
            default:
                std::cout << "Unknown event type received: " << event.type << std::endl;
                break;
        }
    }
}

bool GameServer::shouldTerminate() {
    // TODO: Make a more complex logic to check if the server should terminate
    // E.g. if sigint is caught
    return !_running;
}

void GameServer::changeDifficulty(float ratio) {
    if (ratio != 0 && ratio != 1) {
        for (auto &&[id, enemy] : IndexedZipper(_registry.getComponents<component::Enemy>())) {
            auto &enemy_health = _registry.getComponents<component::Health>()[id].value();
            enemy_health.currentHealth *= ratio;
            enemy_health.maxHealth *= ratio;
       }
    }
}

uint16_t GameServer::getPlayerAmount() const {
    return _connected_players;
}

uint16_t GameServer::getPort() const {
    return _network.getPort();
}

bool GameServer::isFull() const {
    return _connected_players >= MAX_CLIENTS;
}
