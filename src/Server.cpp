#include "Server.hpp"

Server::Server() : _listeningSocket(NULL) {}

Server::~Server() { cleanup(); }

void Server::setupSocket(Socket *socket) { _listeningSocket = socket; }

void Server::run() {
  if (!_listeningSocket) {
    throw std::runtime_error("No socket set - call setupSocket() first");
  }

  _isRunning = true;
  struct epoll_event events[1024];
  _epollManager.addFd(_listeningSocket->getFd(), EPOLLIN);
  std::cout << "Listen finished: " << _listeningSocket->getFd() << std::endl;
  while (_isRunning) {
    int nready = _epollManager.waitForEvents(events, 1024);
    if (nready < 0) {
      if (errno == EINTR)
        continue;
      break;
    }
    for (int i = 0; i < nready; ++i) {
      int fd = events[i].data.fd;

      if (fd == _listeningSocket->getFd()) {
        handleNewConnection();
      } else if (events[i].events & EPOLLIN) {
        handleClientData(fd);
      }
    }
  }
  cleanup();
}

void Server::stop() { _isRunning = false; }

void Server::handleNewConnection() {
  struct sockaddr_in clientAddr;
  socklen_t addrLen = sizeof(clientAddr);

  int clientFd = accept(_listeningSocket->getFd(),
                        (struct sockaddr *)&clientAddr, &addrLen);
  if (clientFd < 0) {
    return;
  }
  std::cout << "Accept finished: " << clientFd << std::endl;
  _clients[clientFd] = new Client(clientFd);
  _epollManager.addFd(clientFd, EPOLLIN);
}

void Server::handleClientData(int clientFd) {
  std::map<int, Client *>::iterator it = _clients.find(clientFd);
  if (it == _clients.end()) {
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
  std::map<int, Client *>::iterator it = _clients.find(clientFd);
  if (it != _clients.end()) {
    _epollManager.removeFd(clientFd);
    delete it->second;
    _clients.erase(it);
  }
}

void Server::cleanup() {
  for (std::map<int, Client *>::iterator it = _clients.begin();
       it != _clients.end(); ++it) {
    _epollManager.removeFd(it->first);
    delete it->second;
  }
  _clients.clear();
}
