#include "Server.hpp"
#include "Socket.hpp"
#include <iostream>
#include <unistd.h>

int main(void) {
    try {
        Server server;
        Socket *socket = new Socket(9191);
        server.setupSocket(socket);

        if (listen(socket->getFd(), 5) < 0) {
            delete socket;
            throw std::runtime_error("Failed to listen on socket");
        }

        server.run();
        delete socket;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return (1);
    }

    return 0;
}
