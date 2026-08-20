// /*
// ** EPITECH PROJECT, 2024
// ** rtype
// ** File description:
// ** on_receive
// */

#include "GameClient.hpp"

#include "packet/SnapshotPacket.hpp"

void GameClient::onReceive(ENetEvent &event) {
    // same with switch
    switch (_state) {
        case ClientState::WAITING_FOR_LOBBY:
            std::cout << "Received packet in lobby" << std::endl;
            onReceiveInLobby(event);
            break;
        case ClientState::IN_GAME:
            std::cout << "Received packet in game" << std::endl;
            onReceiveInGame(event);
            break;
        default:
            break;
    }
}
