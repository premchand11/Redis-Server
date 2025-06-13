#include "../include/RedisServer.h"
#include<iostream>
#include<thread>

int main(int argc, char* argv[]) {
    int port=6379;
    if(argc>=2)port=std::stoi(argv[1]);

    RedisServer server(port);

    //background persistance: dump database  every 360 seconds
    std::thread persistanceThread([]() {
        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(360));
        }
    });
    persistanceThread.detach();


    server.run();
    return 0;
}