#include "../include/RedisServer.h"
#include "../include/RedisDatabase.h"
#include <iostream>

int main(int argc, char* argv[]) {
    int port = 6379; // Default port
    if (argc >= 2) port = std::stoi(argv[1]);

    if (RedisDatabase::getInstance().load("dump.my_rdb"))
        std::cout << "Database Loaded From dump.my_rdb\n";
    else
        std::cout << "No dump found or load failed; starting with an empty database.\n";

    RedisServer server(port);
    server.run();
    return 0;
}