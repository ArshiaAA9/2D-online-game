#pragma once
#include "network/network.hpp"
#include "network/packet.hpp"

class NetworkManager {
public:
    // Network Interfaces
    bool startServer(uint16_t port);
    bool startClient();

    // TODO: read the ip from settings
    bool connectToHost(const char* ip = "127.0.0.1", uint16_t port = 55555);

    bool sendPacketToHost(SE::Packet packet);
    void networkUpdate();

private:
    void sendWorldData();
    // used for polymorphism. can either be NetworkServer or NetworkClient
    std::unique_ptr<Network> m_network = nullptr;
};
