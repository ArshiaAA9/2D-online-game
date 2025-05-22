#include "network_client.hpp"

#include <enet/enet.h>

#include "network.hpp"

//---------------------SETTERS/GETTERS--------------------
NetworkType NetworkClient::getType() const { return m_networkType; }

const ENetAddress& NetworkClient::getAddress() { return m_serverAddress; }

// TODO: validate the address
void NetworkClient::setAddress(ENetAddress address) { m_serverAddress = address; }

const ENetPeer& NetworkClient::getPeer() { return *m_enetServerPeer; }

// TODO: validate the peer
void NetworkClient::setPeer(ENetPeer* peer) { m_enetServerPeer = peer; }

ENetHost& NetworkClient::getEnetHost() { return *m_enetClient; }

const ENetEvent& NetworkClient::getHostEvent() { return m_enetEvent; }

//---------------------CLIENT--------------------
bool NetworkClient::start() {
    if (m_enetClient != nullptr) {
        // checks if client is already running
        std::cerr << "Client host is already running\n";
        return false;
    }
    m_enetClient = enet_host_create(
        nullptr, // nullptr for client
        1,       // only allow one outgoing connection
        2,       // allow up to 2 channels to be used, 0 and 1client
        0,       // assume any amount of incoming bandwidth
        0        // assume any amount of outgoing bandwidth
    );
    if (m_enetClient == nullptr) {
        std::cerr << "Error accured while starting ENet client host";
        return false;
    }
    std::cout << "Client host started: " << m_enetClient->address.host << " at port " << m_enetClient->address.port
              << "\n";
    return true;
}

bool NetworkClient::end() {
    if (m_enetClient == nullptr) {
        std::cerr << "Error accured while closing ENet client host: client host does not exist";
        return false;
    }
    enet_host_destroy(m_enetClient);
    m_enetClient = nullptr;
    return true;
}

// TODO: SEND ACTUAL GOOD DATA
void NetworkClient::sendPacket(const SE::Packet& packet, ENetPeer* peer) {
    ENetPacket* pPacket = enet_packet_create(
        &packet,                  // packet itself
        sizeof(SE::Packet),       // size of the packet. Packet is the struct
        ENET_PACKET_FLAG_RELIABLE // ensures it is recevied
    );
    enet_peer_send(peer, 0, pPacket);
    enet_host_flush(m_enetClient);
}

void NetworkClient::pollEvents() {}

void NetworkClient::handlePacket(const ENetPacket* packet) {}
