#include "include/RedisServer.h"


#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>



static RedisServer* globalServer = nullptr;


RedisServer::RedisServer(int port) : port(port),server_socket(-1),running(true) {
    globalServer = this;
}

void RedisServer::shutdown() {
    running = false;
    if (server_socket != -1) {
        close(server_socket);
        server_socket = -1;
    }
    std::cout<< "Server shutdown successfully." << std::endl;
}

void RedisServer::run() {
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        std::cerr << "Failed to create socket." << std::endl;
        return;
    }

    int opt = 1;
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        sockaddr_in serverAddr{};
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = INADDR_ANY;
        serverAddr.sin_port = htons(port);

        if(bind(server_socket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
            std::cerr << "Failed to bind socket." << std::endl;
            close(server_socket);
            return;
        }
        if(listen(server_socket, 7) < 0) {
            std::cerr << "Failed to listen on socket." << std::endl;
            close(server_socket);
            return;
        }
        std::cout << "Server is running on port " << port << std::endl;
        



    }
}