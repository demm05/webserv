#include "Socket.hpp"
#include <unistd.h>
#include <iostream>

int main(void) {
    Socket sk(9191);
    listen(sk.getFd(), 5);
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int client_fd = accept(sk.getFd(), (struct sockaddr *)&client_addr, &client_len);
    char buffer[1024] = {0};
    int bytes_received = recv(client_fd, buffer, 1024, 0);
    buffer[bytes_received] = '\0';
    std::cout << buffer;
    close(client_fd);
    return 0;
}
