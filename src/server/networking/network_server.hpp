#pragma once
#include <enet/enet.h>

#include <iostream>

class NetworkServer {
public:
    NetworkServer() {
        if (enet_initialize() != 0) {
            std::cerr << "error initializing ENet\n";
        }
        m_enetAddress.host = ENET_HOST_ANY;
        m_enetAddress.port = 5555;
    }

    ~NetworkServer() { enet_deinitialize(); }

    // maybe give it port as a param
    bool startServer();
    bool endServer();

    void enetEventLoop();

private:
    // CHANGEABLE CODE DEPENDING ON HOW SCOKETS AND COMMUNICATION BETWEEN SERVER AND CLIENTS WORK
    ENetAddress m_enetAddress;
    ENetHost* m_enetServer = nullptr;
    ENetEvent m_enetEvent;
};
