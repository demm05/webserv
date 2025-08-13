#pragma once

#include "Socket.hpp"
#include "EpollManager.hpp"
#include "Client.hpp"
#include <cerrno>
#include <iostream>
#include <map>

class Server {
public:
    Server();
    ~Server();

    void setupSocket(Socket *socket);
    void run();
    void stop();

private:
    Socket *listeningSocket_;
    EpollManager epollManager_;
    std::map<int, Client *> clients_;
    bool isRunning_;

    void handleNewConnection();
    void handleClientData(int clientFd);
    void handleClientDisconnection(int clientFd);

    void cleanup();

    Server(const Server &other);
    Server &operator=(const Server &other);
};