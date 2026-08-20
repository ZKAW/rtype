/*
** EPITECH PROJECT, 2024
** Rtype [WSL: Ubuntu]
** File description:
** main
*/

#include "GameClient.hpp"

int main(int ac, char **av)
{
    if (ac != 3) {
        std::cerr << "Usage: ./client <host> <port>\n";
        return 1;
    }

    try {
        const std::string host = av[1];
        const uint16_t port = std::stoi(av[2]);

        GameClient client(host, port);

        client.init();
        client.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 84;
    }
    return 0;
}
