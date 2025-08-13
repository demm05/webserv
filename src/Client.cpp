#include "Client.hpp"
#include <unistd.h>

Client::Client(int fd) : fd_(fd), connected_(true) {
}

Client::~Client() {
    disconnect();
}

bool Client::isConnected() const {
    return connected_;
}

void Client::disconnect() {
    if (connected_ && fd_ >= 0) {
        close(fd_);
        connected_ = false;
    }
}

int Client::readData(char *buffer, size_t size) {
    if (!connected_)
        return (-1);
    int readBytes = recv(fd_, buffer, size, 0);
    if (readBytes <= 0)
        connected_ = false;
    return (readBytes);
}

int Client::writeData(const char *data, size_t size) {
    if (!connected_)
        return (-1);
    return (send(fd_, data, size, 0));
}
