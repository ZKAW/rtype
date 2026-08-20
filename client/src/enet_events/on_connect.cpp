/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** on_connect
*/

#include "GameClient.hpp"

void GameClient::onConnect([[maybe_unused]] ENetEvent &event)
{
    std::cout << "Connected to server with port: " << event.peer->address.port
              << std::endl;
}
