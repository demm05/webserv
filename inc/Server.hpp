/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 19:46:47 by szhong            #+#    #+#             */
/*   Updated: 2025/08/15 19:49:10 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#pragma once

#include "Client.hpp"
#include "Socket.hpp"
#include "EpollManager.hpp"
#include <map>

class Server {
public:
    Server();
    ~Server();

    void setupSocket(Socket *socket);
    void run();
    void stop();

private:
    Socket *listeningSocket_;
    EpollManager epollManager_;
    std::map<int, Client *> clients_;
    bool isRunning_;

    void handleNewConnection();
    void handleClientData(int clientFd);
    void handleClientDisconnection(int clientFd);

    void cleanup();

    Server(const Server &other);
    Server &operator=(const Server &other);
};
