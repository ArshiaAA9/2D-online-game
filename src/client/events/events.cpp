#include "events.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_video.h>

#include "../game/game.hpp"
#include "SunnyEngine/Types.h"

bool Events::loop() {
    while (SDL_PollEvent(&m_sdlEvent)) {
        switch (m_sdlEvent.type) {
            case SDL_EVENT_QUIT:
                return false;
                break;
            case SDL_EVENT_KEY_DOWN:
                // keyevents
                keydownEvents();
                break;
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                mouseButtonUpEvents();
                break;
        }
    }
    return true;
}

// interfaces:
SDL_Event& Events::getEventVar() { return m_sdlEvent; }

void Events::keydownEvents() {
    SE::ObjectPtr mainChar = m_game.getMainChar();
    switch (m_sdlEvent.key.key) {
        case SDLK_W:
            m_game.moveObject(mainChar, SE::Vector2(0, 1000));
            break;
        case SDLK_D:
            m_game.moveObject(mainChar, SE::Vector2(1000, 0));
            break;
        case SDLK_A:
            m_game.moveObject(mainChar, SE::Vector2(-1000, 0));
            break;
        case SDLK_S:
            m_game.moveObject(mainChar, SE::Vector2(0, -1000));
            break;
        case SDLK_SPACE:
            m_game.stopObject(mainChar);
            break;
    }
}

void Events::mouseButtonUpEvents() {
    switch (m_sdlEvent.button.button) {}
}
