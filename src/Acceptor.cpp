#include <iostream>
#include "InitiationDispatcher.hpp"
#include "Reactor.hpp"
#include "Socket.hpp"

Acceptor::Acceptor(int port) : socket_(NULL), port_(port) {
    setupListenSocket();
}

Acceptor::~Acceptor() {
    delete socket_;
}

void Acceptor::setupListenSocket() {
    socket_ = new Socket(port_);
    if (listen(socket_->getFd(), 10) < 0) {
        delete socket_;
        socket_ = NULL;
        throw std::runtime_error("Failed to listen on socket: " + std::string(strerror(errno)));
    }
    std::cout << "Listening on port " << port_ << std::endl;
}

void Acceptor::handleEvent(uint32_t events) {
    if (events & EPOLLIN) {
        acceptNewConnection();
    }
}

int Acceptor::getHandle() const {
    return socket_ ? socket_->getFd() : -1;
}

void Acceptor::acceptNewConnection() {
    struct sockaddr_in clientaddr;
    socklen_t len = sizeof(clientaddr);

    int clientFd = accept(socket_->getFd(), (struct sockaddr *)&clientaddr, &len);
    if (clientFd < 0) {
        std::cerr << "Accept error: " << strerror(errno) << std::endl;
        return;
    }
    std::cout << "Accept finished: " << clientFd << std::endl;

    Reactor *clientHandler = new Reactor(clientFd);
    InitiationDispatcher::getInstance().registerHandler(clientHandler);
}