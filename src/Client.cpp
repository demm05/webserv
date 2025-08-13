#include "Client.hpp"
#include <unistd.h>

Client::Client(int fd) : _fd(fd), _connected(true) {}

Client::~Client() { disconnect(); }

void Client::disconnect() {
  if (_connected && _fd >= 0) {
    close(_fd);
    _connected = false;
  }
}

int Client::readData(char *buffer, size_t size) {
  if (!_connected)
    return (-1);
  int readBytes = recv(_fd, buffer, size, 0);
  if (readBytes <= 0)
    _connected = false;
  return (readBytes);
}

int Client::writeData(const char *data, size_t size) {
  if (!_connected)
    return (-1);
  return (send(_fd, data, size, 0));
}
