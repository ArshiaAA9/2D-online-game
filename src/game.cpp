#include "game.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_pixels.h>
#include <SunnyEngine/Physics.h>

#include <cstdint>
#include <memory>

#include "network/network_client.hpp"
#include "network/network_server.hpp"
#include "types.hpp"

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

    // main loop
    while (m_event.loop()) {
        m_world.step(dt);
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
    m_network = std::make_unique<NetworkServer>();
    return m_network->start();
}

bool Game::connectToHost() {
    m_network = std::make_unique<NetworkClient>();
    return m_network->start();
}
