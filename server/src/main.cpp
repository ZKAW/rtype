/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** main
*/

/* #include "server.hpp" */
#include "GameServer.hpp"
#include "lobby_manager/LobbyManager.hpp"
#include "lobby_server/LobbyServer.hpp"

//TODO : reset client connection for reroot the client with the new port

int main(int argc, char* argv[]) {
    try {
        if (argc != 3)
            throw std::invalid_argument("Usage: " + std::string(argv[0]) + " <port> <client_max>");
        uint16_t port = atoi(argv[1]); // Port to host the server on
        size_t max_clients = atoi(argv[2]); // Maximum number of clients to host

        // GameServer server(port, max_clients);
        // server.init();
        // server.run();
        LobbyServer lobby_server(port, port + 1);
        lobby_server.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
