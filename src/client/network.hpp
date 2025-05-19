#pragma once
#include <enet/enet.h>

#include <array>
#include <iostream>

#include "packet.hpp"

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

protected:
    virtual void handlePacket(const ENetPacket* packet) = 0;
};

class NetworkClient : public Network {
public:
    bool start() override;
    bool end() override;

    bool connectToServer(const char* ip = "127.0.0.1");
    bool disconnectFromServer();

    void pollEvents() override;
    void sendPacket(SE::Packet packet, ENetPeer* peer) override;

private:
    void handlePacket(const ENetPacket* packet) override;

    ENetHost* m_enetClient = nullptr;
    ENetEvent m_enetEvent;
    ENetPeer* m_enetServerPeer = nullptr;
    ENetAddress m_serverAddress;
};

class NetworkServer : public Network {
public:
    NetworkServer(uint16_t port = 5555) {
        m_enetAddress.host = ENET_HOST_ANY;
        m_enetAddress.port = port;
    }

    bool start() override;
    bool end() override;

    bool listenForClients(); // Replaces connectToHost
    bool disconnectPeer();

    void pollEvents() override;
    void sendPacket(SE::Packet packet, ENetPeer* peer) override;

private:
    void handlePacket(const ENetPacket* packet) override;

    ENetAddress m_enetAddress;
    ENetHost* m_enetServer = nullptr;
    ENetEvent m_enetEvent;
    // m_enetPeers{} means its declaired as = {nullptr, ... , nullptr}
    // it uses the default value of the type and since its a pointer array
    // default type is nullptr
    std::array<ENetPeer*, 4> m_enetPeers{};
};
