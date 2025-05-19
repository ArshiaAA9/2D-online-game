#pragma once

#include <SDL3/SDL_events.h>

class Game;
class Sdl;

class Events {
public:
    // FIX: error with initalization
    explicit Events(Game& game)
        : m_game(game) {}

    // main event loop with PollEvent()
    bool loop();

    SDL_Event& getEventVar();

private:
    // these functions are used in loop inside the switch cases
    void keydownEvents();
    void mouseButtonUpEvents();

    Game& m_game;
    SDL_Event m_sdlEvent;
};
