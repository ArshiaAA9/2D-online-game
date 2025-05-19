#pragma once
#include "network.hpp"

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
