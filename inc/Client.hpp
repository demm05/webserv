#pragma once

#include <stdlib.h>
#include <sys/socket.h>

class Client {
public:
    explicit Client(int fd);
    ~Client();

    int getFd() const;
    bool isConnected() const;
    void disconnect();

    int readData(char *buffer, size_t size);
    int writeData(const char *data, size_t size);

private:
    int fd_;
    bool connected_;

    Client(const Client &other);
    Client &operator=(const Client &other);
};