#pragma once
#include <enet/enet.h>

#include <iostream>

#include "../../common/packet_types.hpp"

class NetworkClient {
public:
    NetworkClient() {
        if (enet_initialize() != 0) {
            std::cerr << "error initializing ENet\n";
        }
    }

    bool startClient();
    bool endClient();

    bool connectToServer();
    bool dissconnectFromServer();

    void enetEventLoop();
    void sendPacketToServer(Packet packet);

private:
    ENetHost* m_enetClient;
    ENetEvent m_enetEvent;
    ENetPeer* m_enetPeer;
    ENetAddress m_serverAddress;
};
