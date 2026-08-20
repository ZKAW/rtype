/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** GameClient
*/

#include "GameClient.hpp"
#include "ecs/systems/DrawSystem.hpp"
#include "entity/allEntities.hpp"

//debug
#include "../debug/DrawHitbox.hpp"
#include "containers/zipper/IndexedZipper.hpp"

GameClient::GameClient(const std::string &host, const uint16_t &port)
    :  AGameCore(std::make_shared<sdl::SDLWrapper>()), _network(host, port), _peer(nullptr)

{
    connect();
}

GameClient::~GameClient()
{
    if (_peer && _peer->state == ENET_PEER_STATE_CONNECTED) {
        enet_peer_disconnect(_peer, 0); // Send a disconnection request to the server
        ENetEvent event;
        while (enet_host_service(_network.getHost().get(), &event, DISCONNECT_TIMEOUT_MS) > 0) {
            if (event.type == ENET_EVENT_TYPE_DISCONNECT) {
                std::cout << "Disconnected from server." << std::endl;
                break;
            }
        }
    }
}

void GameClient::init() {
    _graphicWrapper->createWindow("Game", WINDOW_WIDTH, WINDOW_HEIGHT);
}

void GameClient::handlePacket() {
    ENetEvent event;
    while (enet_host_service(_network.getHost().get(), &event, 0) > 0) {
        switch (event.type) {
            case ENET_EVENT_TYPE_CONNECT:
                onConnect(event);
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                onReceive(event);
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                onDisconnect(event);
                break;
            default:
                std::cout << "Unknown event type received: " << event.type << std::endl;
                break;
        }
    }
}

void GameClient::handleEvents() {
    handlePacket();
    if (_state != ClientState::IN_GAME) {
        // std::cout << "Waiting for lobby (not in game)" << std::endl;
        return;
    }

    std::list<InputEvent> input_event_list = _graphicWrapper->getInputEvents();
    for (InputEvent &input_event : input_event_list) {
        if (input_event.key == InputKey::CLOSE) {
            std::cout << "Sending disconnect packet to server." << std::endl;
            _running = false;
            return;
        }
        flatbuffers::FlatBufferBuilder builder;
        auto input_event_packet = fbs::CreateInputEventPacket(
            builder,
            static_cast<fbs::KeyType>(input_event.type),
            static_cast<fbs::KeyState>(input_event.state),
            input_event.timestampSec,
            input_event.repeat,
            static_cast<fbs::InputKey>(input_event.key)
        );

        /* _network.send(_peer, input_event_packet, builder, fbs::PacketType::PacketType_INPUT_EVENT); */
        _network.send<fbs::InputEventPacket>(_peer, builder, input_event_packet, fbs::PacketType::PacketType_INPUT_EVENT);
    }
}

void GameClient::render() {
    if (_state != ClientState::IN_GAME) {
        // std::cout << "Waiting for lobby (not in game)" << std::endl;
        return;
    }
    static DrawSystem draw_system;
    static std::any renderer_any = _graphicWrapper->getWindow();
    static auto renderer = std::any_cast<std::shared_ptr<SDL_Renderer>>(renderer_any);

    SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, MAX_OPACITY);
    SDL_RenderClear(renderer.get());

    draw_system(this->_registry, _graphicWrapper, renderer);

    // debug
    // static DrawHitbox drawHitbox;
    // drawHitbox(this->_registry);
    //

    SDL_RenderPresent(renderer.get());
}

auto GameClient::shouldTerminate() -> bool {
    // TODO: Could add more logic like checking if the player has lost all lives etc.
    // NOTE: Maybe this func is useless as we could just check the _running state
    return !_running;
}
