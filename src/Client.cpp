#include "Client.hpp"
#include <unistd.h>

Client::Client(int fd) : fd_(fd), isConnected_(true) {
}

Client::~Client() {
    disconnect();
}

bool Client::getIsConnected() const {
    return isConnected_;
}

void Client::disconnect() {
    if (isConnected_ && fd_ >= 0) {
        close(fd_);
        isConnected_ = false;
    }
}

int Client::readData(char *buffer, size_t size) {
    if (!isConnected_)
        return (-1);
    int readBytes = recv(fd_, buffer, size, 0);
    if (readBytes <= 0)
        isConnected_ = false;
    return (readBytes);
}

int Client::writeData(const char *data, size_t size) {
    if (!isConnected_)
        return (-1);
    return (send(fd_, data, size, 0));
}
