#pragma once
#include <enet/enet.h>

#include "network.hpp"

class NetworkClient : public Network {
public:
    NetworkClient()
        : Network(NetworkType::NetworkClient) {}

    NetworkType getType() const override;

    const ENetAddress& getAddress() override;
    virtual void setAddress(ENetAddress address) override;

    const ENetPeer& getPeer() override;
    void setPeer(ENetPeer* peer) override;

    ENetHost& getEnetHost() override;
    const ENetEvent& getHostEvent() override;

    bool start() override;
    bool end() override;

    void pollEvents() override;
    void sendPacket(const SE::Packet& packet, ENetPeer* peer) override;

private:
    bool connectToServer(const char* ip = "127.0.0.1");

    void handlePacket(const ENetPacket* packet) override;

    ENetHost* m_enetClient = nullptr;
    ENetPeer* m_enetServerPeer = nullptr;
    ENetEvent m_enetEvent;
    ENetAddress m_serverAddress;
};
