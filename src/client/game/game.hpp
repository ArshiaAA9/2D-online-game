#pragma once

#include "../events/events.hpp"
#include "../rendering/renderer.hpp"
#include "../settings/settings.hpp"

class Game {
public:
    explicit Game()
        : m_world([this] {
            const auto [w, h] = m_settings.getWidthHeight();
            return SE::PhysicsWorld(w, h);
        }())
        , m_event(*this)
        , m_renderer(m_settings) {
        m_renderer.init();
    }

    // main game function
    void start();

    // set main character object
    void setMainChar(SE::ObjectPtr main);
    // get main character object
    SE::ObjectPtr getMainChar();

    // creation functions
    SE::ObjectPtr createRect(float x, float y, float mass, float width, float height, SDL_FColor color, float angle);

    SE::ObjectPtr createStaticRect(float x, float y, float width, float height, SDL_FColor color, float angle);

    // movment functions
    void moveObject(SE::ObjectPtr object, SE::Vector2 amount);
    void moveObjectTo(SE::ObjectPtr object, SE::Vector2 position);
    void stopObject(SE::ObjectPtr object);

private:
    Settings m_settings; // Must be initialized first

    // GAME RELATED MEMBERS:
    SE::PhysicsWorld m_world;
    SE::ObjectPtr m_mainChar;

    // SDL RELATED MEMBERS:
    Events m_event;
    Renderer m_renderer; // Depends on settings
};
