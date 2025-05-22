#include "game.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_pixels.h>
#include <SunnyEngine/Physics.h>
#include <enet/enet.h>

#include <cstdint>
#include <iostream>
#include <memory>

#include "network/network_client.hpp"
#include "network/network_server.hpp"

//-------------------MAIN GAME LOOP-------------------
void Game::start() {
    // phyiscs:
    m_world.setGravity(SE::Vector2(0, 0));
    float dt = 1.0f / 60.0f;
    float delay = 1000.0f / 60.0f;
    // main character TODO:
    const auto& [w, h] = m_settings.getWidthHeight();
    SDL_FColor mainCharColor = {255, 0, 0, 255};
    m_mainChar = createRect(w / 2.0f, (h - h / 2.0f), 1, 100, 100, mainCharColor, 0);

    // NOTE: MUST BE USED BEFORE WORLD AND UPDATED
    // EVERYTIME A BIG OBJECT IS ADDED
    m_world.cD.m_grid.updateCellDimensions();

    std::string mode;
    while (true) {
        std::cout << "enter mode (s)erver or (c)lient:\n";
        std::cin >> mode;
        if (mode == "s") {
            if (startServer(55555)) break;
            // handle errors:
        } else if (mode == "c") {
            if (startClient()) break;
            // handle errors:
        }
        std::cout << "unvalid input\n";
    }

    // main loop
    while (m_event.loop()) {
        // check the network events
        m_network->pollEvents();
        // update physics
        m_world.step(dt);
        // update the screen
        m_renderer.update(m_world);
        SDL_Delay(delay);
    }
}

SE::ObjectPtr Game::getMainChar() { return m_mainChar; }

//----------------------OBJECT CREATION----------------------
SE::ObjectPtr Game::createRect(float x, float y, float mass, float width, float height, SDL_FColor color, float angle) {
    SE::ObjectPtr pObject = m_world.Handler.createRectObj(x, y, mass, width, height, angle);
    m_renderer.addRenderPair(pObject, color);
    return pObject;
}

SE::ObjectPtr Game::createStaticRect(float x, float y, float width, float height, SDL_FColor color, float angle) {
    SE::ObjectPtr pObject = m_world.Handler.createStaticRect(x, y, width, height, angle);
    m_renderer.addRenderPair(pObject, color);
    return pObject;
}

//----------------------OBJECT MOVEMENT----------------------
void Game::moveObject(SE::ObjectPtr object, SE::Vector2 amount) { object->applyForce(amount); }

void Game::stopObject(SE::ObjectPtr object) { object->setVelocity(SE::Vector2(0, 0)); }

void Game::moveObjectTo(SE::ObjectPtr object, SE::Vector2 position) { object->transform.moveTo(position); }

//----------------------NETWORK----------------------
// TODO: apparantly can use the visitor pattern or downcast to use child specific method
//
bool Game::startServer(uint16_t port) {
    m_network = std::make_unique<NetworkServer>(port);
    return m_network->start();
}

bool Game::startClient() {
    if (m_network != nullptr) {
        std::cerr << "a server or a client already started\n";
        return false;
    }
    m_network = std::make_unique<NetworkClient>();
    return m_network->start();
}

// TODO: CALL THIS FUNCTION IN CORRECT PLACE AND TEST
bool Game::connectToHost(const char* ip, uint16_t port) {
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
