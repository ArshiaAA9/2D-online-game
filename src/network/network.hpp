#pragma once
#include <enet/enet.h>

#include <iostream>

#include "packet.hpp"

// for easier including
class NetworkServer;
class NetworkClient;

class Network {
public:
    Network() {
        if (enet_initialize() != 0) {
            std::cerr << "error initializing ENet\n";
        }
    }

    virtual ~Network() { enet_deinitialize(); }

    virtual bool start() = 0;
    virtual bool end() = 0;

    virtual void pollEvents() = 0;
    virtual void sendPacket(SE::Packet packet, ENetPeer* peer) = 0;

    bool connectToServer(const char* ip = "127.0.0.1");

protected:
    virtual void handlePacket(const ENetPacket* packet) = 0;
};
