#include "Reactor.hpp"
#include "InitiationDispatcher.hpp"
#include <iostream>
#include "HttpProcessor.hpp"

Reactor::Reactor(int clientFd) : clientFd_(clientFd), readLength_(0), writeLength_(0) {
    memset(readBuffer_, 0, BUFFER_LENGTH);
    memset(writeBuffer_, 0, BUFFER_LENGTH);
}

Reactor::~Reactor() {
    if (clientFd_ >= 0) {
        close(clientFd_);
    }
}

void Reactor::handleEvent(uint32_t events) {
    if (events & EPOLLIN) {
        handleRead();
    }
    if (events & EPOLLOUT) {
        handleWrite();
    }
}

int Reactor::getHandle() const {
    return clientFd_;
}

// TODO review recv_cb function logic
void Reactor::handleRead() {
    memset(readBuffer_, 0, BUFFER_LENGTH);
    int count = recv(clientFd_, readBuffer_, BUFFER_LENGTH, 0);
    if (count == 0) {
        std::cout << "Client disconnect: " << clientFd_ << std::endl;
        InitiationDispatcher::getInstance().removeHandler(clientFd_);
        delete this;
        return;
    } else if (count < 0) {
        std::cerr << "Recv error: " << strerror(errno) << std::endl;
        InitiationDispatcher::getInstance().removeHandler(clientFd_);
        delete this;
        return;
    }
    readLength_ = count;
    std::cout << "RECV: " << readBuffer_ << std::endl;
    // writeLength_ = readLength_;
    // memcpy(writeBuffer_, readBuffer_, writeLength_);
    // ===== NEW HTTP PROCESSING =====
    // Check if this looks like an HTTP request
    if (strncmp(readBuffer_, "GET", 3) == 0 || strncmp(readBuffer_, "POST", 4) == 0 ||
        strncmp(readBuffer_, "HEAD", 4) == 0) {

        // Process as HTTP request
        HttpProcessor httpProcessor;
        std::string httpResponse = httpProcessor.processRequest(readBuffer_, readLength_);
        // Copy HTTP response to write buffer
        writeLength_ = std::min(httpResponse.length(), (size_t)(BUFFER_LENGTH - 1));
        memcpy(writeBuffer_, httpResponse.c_str(), writeLength_);

        std::cout << "Generated HTTP response (" << writeLength_ << " bytes)" << std::endl;
    } else {
        writeLength_ = readLength_;
        memcpy(writeBuffer_, readBuffer_, writeLength_);
        std::cout << "Echo response" << std::endl;
    }
    InitiationDispatcher::getInstance().getEpollManager().modifyFd(clientFd_, EPOLLOUT);
}

// TODO review send_cb function logic
void Reactor::handleWrite() {
    if (writeLength_ > 0) {
        int count = send(clientFd_, writeBuffer_, writeLength_, 0);
        if (count > 0) {
            std::cout << "SEND: " << count << " bytes" << std::endl;
        }
    }
    InitiationDispatcher::getInstance().getEpollManager().modifyFd(clientFd_, EPOLLIN);
}