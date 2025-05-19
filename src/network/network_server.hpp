#pragma once
#include <enet/types.h>

#include <array>
#include <cstdint>

#include "network.hpp"

class NetworkServer : public Network {
public:
    NetworkServer(uint16_t port = 5555) {
        m_enetAddress.host = ENET_HOST_ANY;
        m_enetAddress.port = port;
    }

    void setPort(uint16_t port);
    enet_uint16 getPort();

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
