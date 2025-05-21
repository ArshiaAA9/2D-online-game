#pragma once
#include <enet/enet.h>

#include <iostream>

#include "packet.hpp"

// for easier including
class NetworkServer;
class NetworkClient;

enum class NetworkType { Network, NetworkServer, NetworkClient };

class Network {
public:
    Network(NetworkType type)
        : m_networkType(type) {
        if (enet_initialize() != 0) {
            std::cerr << "error initializing ENet\n";
        }
    }

    virtual ~Network() { enet_deinitialize(); }

    virtual const ENetAddress& getAddress() = 0;
    virtual void setAddress(ENetAddress address) = 0;

    virtual const ENetPeer& getPeer() = 0;
    virtual void setPeer(ENetPeer* peer) = 0;

    // no setter gets initialized in start() method
    virtual const ENetHost& getEnetHost() = 0;
    virtual const ENetEvent& getHostEvent() = 0;

    virtual bool start() = 0;
    virtual bool end() = 0;

    virtual void pollEvents() = 0;
    virtual void sendPacket(const SE::Packet& packet, ENetPeer* peer) = 0;

    bool connectToServer(const char* ip = "127.0.0.1");

protected:
    virtual void handlePacket(const ENetPacket* packet) = 0;

    NetworkType m_networkType = NetworkType::Network;
};
