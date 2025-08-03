#include "Socket.hpp"
#include <unistd.h>
#include <iostream>
#include <string.h>

/*
int main(void) {
    Socket sk(9191);
    listen(sk.getFd(), 5);
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    while (1) {
        int client_fd = accept(sk.getFd(), (struct sockaddr *)&client_addr, &client_len);
        char buffer[1024] = {0};
        int bytes_received = recv(client_fd, buffer, 1024, 0);
        buffer[bytes_received] = '\0';
        std::cout << buffer;
        const char *reply =
            "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nabc";
        send(client_fd, reply, strlen(reply), 0);
        close(client_fd);
    }
    return 0;
}
*/
