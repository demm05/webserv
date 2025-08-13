#include "EpollManager.hpp"


EpollManager::EpollManager() : _epollFd(-1) {
    _epollFd = epoll_create1(0);
    if (_epollFd < 0) {
        throw std::runtime_error("Failed to create epoll instance: " +
                                 std::string(strerror(errno)));
    }
}

EpollManager::~EpollManager() {
    if (_epollFd >= 0) {
        close(_epollFd);
    }
}

void EpollManager::addFd(int fd, uint32_t events) {
    struct epoll_event eventStruct;
    eventStruct.events = events;
    eventStruct.data.fd = fd;

    if (epoll_ctl(_epollFd, EPOLL_CTL_ADD, fd, &eventStruct) < 0) {
        throw std::runtime_error("Failed to add fd to epoll: " + std::string(strerror(errno)));
    }
}

void EpollManager::removeFd(int fd) {
    if (epoll_ctl(_epollFd, EPOLL_CTL_DEL, fd, NULL) < 0) {
        throw std::runtime_error("Failed to add fd to epoll: " + std::string(strerror(errno)));
    }
}

void EpollManager::modifyFd(int fd, uint32_t events) {
    struct epoll_event eventStruct;
    eventStruct.events = events;
    eventStruct.data.fd = fd;

    if (epoll_ctl(_epollFd, EPOLL_CTL_MOD, fd, &eventStruct) < 0) {
        throw std::runtime_error("Failed to modify fd in epoll: " + std::string(strerror(errno)));
    }
}

int EpollManager::waitForEvents(struct epoll_event *events, int maxEvents, int timeout) {
    return epoll_wait(_epollFd, events, maxEvents, timeout);
}
