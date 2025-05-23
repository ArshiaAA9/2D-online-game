#include "network_manager.hpp"

#include <SunnyEngine/Types.h>

#include <iostream>
#include <memory>

#include "network/network_client.hpp"
#include "network/network_server.hpp"

//----------------------NETWORK----------------------
bool NetworkManager::startServer(uint16_t port) {
    m_network = std::make_unique<NetworkServer>(port);
    return m_network->start();
}

bool NetworkManager::startClient() {
    if (m_network != nullptr) {
        std::cerr << "a server or a client already started\n";
        return false;
    }
    m_network = std::make_unique<NetworkClient>();
    return m_network->start();
}

// TODO: CALL THIS FUNCTION IN CORRECT PLACE AND TEST
bool NetworkManager::connectToHost(const char* ip, uint16_t port) {
    if (m_network->getType() != NetworkType::NetworkClient) {
        std::cerr << "cant connect from server\n";
        return false;
    }
    ENetAddress address;
    if (enet_address_set_host_ip(&address, ip) != 0) {
        std::cerr << "failed setting ip";
        return false;
    }
    address.port = port;
    ENetHost& clientHost = m_network->getEnetHost();
    ENetEvent clientEvent = m_network->getHostEvent();
    ENetPeer* pPeer = enet_host_connect(&clientHost, &address, 2, 0);
    if (pPeer == nullptr) {
        std::cerr << "error accured while creating peer\n";
        return false;
    }
    if (enet_host_service(&clientHost, &clientEvent, 2000) > 0) {
        if (clientEvent.type == ENET_EVENT_TYPE_CONNECT) {
            std::cout << " connected to: " << clientEvent.peer->address.host << ':' << clientEvent.peer->address.port
                      << '\n';
            enet_host_flush(&clientHost); // Force send immediately
            m_network->setPeer(pPeer);
            return true;
        }
        std::cout << "couldnt connect\n";
        return false;
    }
    std::cerr << "failed connecting to: " << address.host << ":" << address.port << '\n';
    return false;
}

void NetworkManager::sendWorldData() {
    // TODO: learn serialization and use it to write good packets
    // then write this method
}

void NetworkManager::networkUpdate() {
    m_network->pollEvents();
    sendWorldData();
}
