/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** on_disconnect
*/

#include "GameClient.hpp"

void GameClient::onDisconnect(ENetEvent &event)
{
    (void)event;

    std::cout << "Disconnected from server." << std::endl;
    _running = false;
}
