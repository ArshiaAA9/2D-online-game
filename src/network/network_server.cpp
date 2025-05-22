#include "network_server.hpp"

#include <enet/enet.h>
#include <enet/types.h>

#include <iostream>

#include "algorithm"

//---------------------SETTERS/GETTERS--------------------
NetworkType NetworkServer::getType() const { return m_networkType; }

const ENetAddress& NetworkServer::getAddress() { return m_enetAddress; }

// TODO: validate the address
void NetworkServer::setAddress(ENetAddress address) { m_enetAddress = address; }

// TODO: COMPLETE THESE
const ENetPeer& NetworkServer::getPeer() {}

// TODO: COMPLETE THESE
void NetworkServer::setPeer(ENetPeer* peer) {}

ENetHost& NetworkServer::getEnetHost() { return *m_enetServer; }

const ENetEvent& NetworkServer::getHostEvent() { return m_enetEvent; }

//---------------------SERVER--------------------
bool NetworkServer::start() {
    if (m_enetServer != nullptr) {
        std::cerr << "Server already running\n";
        return false;
    }
    m_enetServer = enet_host_create(
        &m_enetAddress, // the address to bind the server host to
        4,              // allow up to 32 clients and/or outgoing connections
        2,              // allow up to 2 channels to be used, 0 and 1
        0,              // assume any amount of incoming bandwidth
        0               // assume any amount of outgoing bandwidth
    );
    if (m_enetServer == nullptr) {
        std::cerr << "Error accured while starting ENet server host";
        return false;
    }
    std::cout << "Server started at: " << m_enetAddress.host << ":" << m_enetAddress.port << "\n";
    return true;
}

bool NetworkServer::end() {
    if (m_enetServer == nullptr) {
        std::cerr << "Error accured while closing ENet server host: Server host does not exist";
        return false;
    }
    // TODO: update clients about the server closing
    enet_host_destroy(m_enetServer);
    m_enetServer = nullptr;
    return true;
}

//---------------------LOOPS--------------------
// TODO: MAKE IT TO RECEVE REAL DATA
// run this every frame or every other frame
void NetworkServer::pollEvents() {
    while (enet_host_service(m_enetServer, &m_enetEvent, 100) > 0) {
        std::cout << "switch\n";
        switch (m_enetEvent.type) {
            case ENET_EVENT_TYPE_CONNECT:
                std::cout << "connect type\n";
                handleConnectedPeer();
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                std::cout << "receive type\n";
                handlePacket(m_enetEvent.packet);
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                std::cout << m_enetEvent.peer->data << "disconnected \n";
                m_enetEvent.peer->data = nullptr;
                break;
            case ENET_EVENT_TYPE_NONE:
                break;
        }
    }
}

void NetworkServer::handleConnectedPeer() {
    // find the first empty array slot (nullptr)
    auto itr = std::find(m_enetPeers.begin(), m_enetPeers.end(), nullptr);
    // check if there is available nullptr
    if (itr != m_enetPeers.end()) {
        // replace the nullptr with new peer
        *itr = m_enetEvent.peer;
        std::cout << "A new client connected from: " << m_enetEvent.peer->address.host << ':'
                  << m_enetEvent.peer->address.port << '\n';
    } else {
        std::cerr << "max peer amout reached, cant add new peer\n";
    }
}

void NetworkServer::handlePacket(const ENetPacket* packet) {
    std::cout << "package length: " << m_enetEvent.packet->dataLength << " containing: " << m_enetEvent.packet->data
              << " from: " << m_enetEvent.peer->address.host << ":" << m_enetEvent.peer->address.port
              << " channel: " << m_enetEvent.channelID << '\n';
    if (packet->dataLength != sizeof(SE::Packet)) {
        std::cerr << "packet size doesnt match!";
        SE::Packet notifyPacket = SE::Packet("packet size doesnt match!");
        ENetPacket* pPacket = enet_packet_create(
            &notifyPacket,            // packet itself
            sizeof(SE::Packet),       // size of the packet. Packet is the struct
            ENET_PACKET_FLAG_RELIABLE // ensures it is recevied
        );
        enet_peer_send(m_enetEvent.peer, 0, pPacket);
        return;
    }
    SE::Packet newPacket;
    // destroy packet now that we are done using it
    enet_packet_destroy(m_enetEvent.packet);

    // for reading the packet
    // std::memcpy(&newPacket, packet->data, sizeof(SE::Packet));
    // std::cout << "packet: " << newPacket.type << "\n";
    // if (newPacket.type == SE::CHAT) std::cout << newPacket.msg;
    // NOTE: might have to use: enet_host_flush(m_enetServer);
}

void NetworkServer::sendPacket(const SE::Packet& packet, ENetPeer* peer) {
    ENetPacket* pPacket = enet_packet_create(&packet, sizeof(packet), ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(peer, 0, pPacket);
}
