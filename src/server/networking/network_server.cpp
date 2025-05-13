#include "network_server.hpp"

#include <enet/enet.h>

#include <iostream>

//---------------------START/END--------------------
bool NetworkServer::startServer() {
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
    std::cout << "Server started at port: " << m_enetAddress.port << "\n";
    return true;
}

bool NetworkServer::endServer() {
    if (m_enetServer == nullptr) {
        std::cerr << "Error accured while closing ENet server host: Server host does not exist";
        return false;
    }
    // TODO: update clients about the server closing
    enet_host_destroy(m_enetServer);
    m_enetServer = nullptr;
    return true;
}

//---------------------LOOP--------------------
// TODO: MAKE IT TO RECEVE REAL DATA
void NetworkServer::enetEventLoop() {
    while (enet_host_service(m_enetServer, &m_enetEvent, 0) > 0) {
        switch (m_enetEvent.type) {
            case ENET_EVENT_TYPE_CONNECT:
                std::cout << "A new client connected from: " << m_enetEvent.peer->address.host << ':'
                          << m_enetEvent.peer->address.port << '\n';
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                handlePacket();
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                std::cout << m_enetEvent.peer->data << " disconnected \n";
                m_enetEvent.peer->data = nullptr;
                break;
            case ENET_EVENT_TYPE_NONE:
                break;
        }
    }
}

void NetworkServer::handlePacket() {
    std::cout << "package length: " << m_enetEvent.packet->dataLength << " containing: " << m_enetEvent.packet->data
              << " from: " << m_enetEvent.peer->data << " channel: " << m_enetEvent.channelID << '\n';
    // destroy packet now that we are done using it
    enet_packet_destroy(m_enetEvent.packet);
}
