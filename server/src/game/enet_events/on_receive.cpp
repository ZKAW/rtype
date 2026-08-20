/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** on_receive
*/

#include "GameServer.hpp"
#include "containers/zipper/Zipper.hpp"

namespace {
    std::string typeToStr(KeyType type)
    {
        switch (type) {
            case KeyType::KEYUP:
                return "KEYUP";
            case KeyType::KEYDOWN:
                return "KEYDOWN";
            default:
                return "UNKNOWN";
        }
    }

    std::string stateToStr(KeyState state)
    {
        switch (state) {
            case KeyState::PRESSED:
                return "PRESSED";
            case KeyState::RELEASED:
                return "RELEASED";
            default:
                return "UNKNOWN";
        }
    }

    std::string keyToStr(InputKey key)
    {
        switch (key) {
            case InputKey::UP:
                return "UP";
            case InputKey::DOWN:
                return "DOWN";
            case InputKey::LEFT:
                return "LEFT";
            case InputKey::RIGHT:
                return "RIGHT";
            default:
                return "UNKNOWN";
        }
    }
}

void GameServer::handleEventsEvent(ENetPeer *peer, const fbs::InputEventPacket *packet)
{
    if (!peer || !packet) {
        std::cerr << "Invalid input event packet received." << std::endl;
        return;
    }
    for (auto &&[player] : Zipper(_registry.getComponents<component::Player>())) {
        if (player.clientId == peer->incomingPeerID) {
            const InputEvent input_event = {
                .type = static_cast<KeyType>(packet->type()),
                .state = static_cast<KeyState>(packet->state()),
                .timestampSec = packet->timestamp_sec(),
                .repeat = packet->repeat(),
                .key = static_cast<InputKey>(packet->key())
            };
            std::cout << "\n\n-------------Received input event from client " << player.clientId << ": " << std::endl;
            std::cout << "Type: " << typeToStr(input_event.type) << std::endl;
            std::cout << "Type (uint8_t): " << static_cast<uint8_t>(input_event.type) << std::endl;
            std::cout << "State: " << stateToStr(input_event.state) << std::endl;
            std::cout << "State (uint8_t): " << static_cast<uint8_t>(input_event.state) << std::endl;
            std::cout << "Timestamp: " << packet->timestamp_sec() << std::endl;
            std::cout << "Repeat: " << packet->repeat() << std::endl;
            std::cout << "Key: " << keyToStr(input_event.key) << std::endl;

            player.inputQueue->addInputEvent(input_event);
            break;
        }
    }
}

void GameServer::onReceive(ENetEvent &event)
{
    /* const fbs::Packet* packet = fbs::GetPacket(event.packet->data); */
    auto packet = PacketHelper::getPacketInfo(event.packet);
    if (!packet.data) {
        std::cerr << "Invalid packet received." << std::endl;
        return;
    }

    // Handle packet based on its type
    switch (packet.type) {
        case fbs::PacketType::PacketType_INPUT_EVENT:
            handleEventsEvent(event.peer, PacketHelper::getPacketData<fbs::InputEventPacket>(packet));
            break;
        default:
            break;
    }
}
