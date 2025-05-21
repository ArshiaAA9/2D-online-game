#pragma once
#include <enet/enet.h>

#include "network.hpp"

class NetworkClient : public Network {
public:
    NetworkClient()
        : Network(NetworkType::NetworkClient) {}

    const ENetAddress& getAddress() override;
    virtual void setAddress(ENetAddress address) override;

    const ENetPeer& getPeer() override;
    void setPeer(ENetPeer* peer) override;

    const ENetHost& getEnetHost() override;
    const ENetEvent& getHostEvent() override;

    bool start() override;
    bool end() override;

    void pollEvents() override;
    void sendPacket(const SE::Packet& packet, ENetPeer* peer) override;

private:
    bool connectToServer(const char* ip = "127.0.0.1");
    void handlePacket(const ENetPacket* packet) override;

    ENetHost* m_enetClient = nullptr;
    ENetEvent m_enetEvent;
    ENetPeer* m_enetServerPeer = nullptr;

    ENetAddress m_serverAddress;
};
