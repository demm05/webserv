#include "Server.hpp"

Server::Server() : listeningSocket_(NULL) {
}

Server::~Server() {
    cleanup();
}

void Server::setupSocket(Socket *socket) {
    listeningSocket_ = socket;
}

void Server::run() {
    if (!listeningSocket_) {
        throw std::runtime_error("No socket set - call setupSocket() first");
    }

    isRunning_ = true;
    struct epoll_event events[1024];
    epollManager_.addFd(listeningSocket_->getFd(), EPOLLIN);
    std::cout << "Listen finished: " << listeningSocket_->getFd() << std::endl;
    while (isRunning_) {
        int nready = epollManager_.waitForEvents(events, 1024);
        if (nready < 0) {
            if (errno == EINTR)
                continue;
            break;
        }
        for (int i = 0; i < nready; ++i) {
            int fd = events[i].data.fd;

            if (fd == listeningSocket_->getFd()) {
                handleNewConnection();
            } else if (events[i].events & EPOLLIN) {
                handleClientData(fd);
            }
        }
    }
    cleanup();
}

void Server::stop() {
    isRunning_ = false;
}

void Server::handleNewConnection() {
    struct sockaddr_in clientAddr;
    socklen_t addrLen = sizeof(clientAddr);

    int clientFd = accept(listeningSocket_->getFd(), (struct sockaddr *)&clientAddr, &addrLen);
    if (clientFd < 0) {
        return;
    }
    std::cout << "Accept finished: " << clientFd << std::endl;
    clients_[clientFd] = new Client(clientFd);
    epollManager_.addFd(clientFd, EPOLLIN);
}

void Server::handleClientData(int clientFd) {
    std::map<int, Client *>::iterator it = clients_.find(clientFd);
    if (it == clients_.end()) {
        return;
    }
    Client *client = it->second;
    char buffer[1024];
    int readBytes = client->readData(buffer, sizeof(buffer) - 1);
    if (readBytes <= 0) {
        handleClientDisconnection(clientFd);
        return;
    }
    buffer[readBytes] = '\0';
    std::cout << "RECV: " << buffer << std::endl;

    int byteSent = client->writeData(buffer, readBytes);
    std::cout << "SEND: " << byteSent << std::endl;
}

void Server::handleClientDisconnection(int clientFd) {
    std::map<int, Client *>::iterator it = clients_.find(clientFd);
    if (it != clients_.end()) {
        epollManager_.removeFd(clientFd);
        delete it->second;
        clients_.erase(it);
    }
}

void Server::cleanup() {
    for (std::map<int, Client *>::iterator it = clients_.begin(); it != clients_.end(); ++it) {
        epollManager_.removeFd(it->first);
        delete it->second;
    }
    clients_.clear();
}
