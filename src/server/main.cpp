#include <iostream>

#include "networking/network_server.hpp"

int main() {
    NetworkServer server = NetworkServer();
    server.startServer();
    std::string ans;

    while (ans != "exit") {
        server.enetEventLoop();
    }
    server.endServer();
    return 0;
}
