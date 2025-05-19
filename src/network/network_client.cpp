#include "network_client.hpp"

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

bool NetworkClient::connectToServer(const char* ip) {
    // TODO: pass ip as a param and save it in settings
    enet_address_set_host(&m_serverAddress, ip);
    m_serverAddress.port = 5555;
    m_enetServerPeer = enet_host_connect(m_enetClient, &m_serverAddress, 2, 0);
    if (m_enetServerPeer == nullptr) {
        std::cerr << "error accured while creating peer\n";
        return false;
    }
    if (enet_host_service(m_enetClient, &m_enetEvent, 5000) > 0 && m_enetEvent.type == ENET_EVENT_TYPE_CONNECT) {
        std::cout << " connected to: " << m_enetEvent.peer->address.host << ':' << m_enetEvent.peer->address.port
                  << '\n';
        return true;
    }
    std::cerr << "error accured while creating connecting\n";
    return false;
}

// TODO: DO THIS
bool NetworkClient::disconnectFromServer() { return true; }

// TODO: SEND ACTUAL GOOD DATA
void NetworkClient::sendPacket(SE::Packet packet, ENetPeer* peer) {
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
