#pragma once

#include "Socket.hpp"
#include "EpollManager.hpp"
#include "Client.hpp"
#include <map>

class Server {
public:
    Server();
    ~Server();

    void setupSocket(Socket *socket);
    void run();
    void stop();

private:
    Socket *_listeningSocket;
    EpollManager _epollManager;
    std::map<int, Client *> _clients;
    bool _isRunning;

    void handleNewConnection();
    void handleClientData(int clientFd);
    void handleClientDisconnection(int clientFd);

    void cleanup();

    Server(const Server &other);
    Server &operator=(const Server &other);
};