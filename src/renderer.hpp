#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SunnyEngine/Physics.h>
#include <bits/stdc++.h> // for std::pair

#include "settings.hpp"

class Renderer {
public:
    explicit Renderer(Settings& settings)
        : m_settings(settings) {}

    void init();
    void update(SE::PhysicsWorld& world);

    // interfaces:
    // adds pairs to a map {const object*: SDL_Color}
    void addRenderPair(SE::ObjectPtr, SDL_FColor color);
    // removes a pair from the map
    void deleteRenderPair(SE::ObjectPtr);
    // returns a contsant reference to renderMap
    // FIX: CHAGNE COLOR TO SPRITE LATER
    const std::unordered_map<SE::ObjectPtr, SDL_FColor>& getRenderMap(); // stores objects with a corresponding color

private:
    // clears screen to white
    void clearScreen();

    // used to draw rects
    void drawRect(const SE::ObjectPtr object, SDL_FColor color);
    void drawFilledRect(const SE::ObjectPtr object, SDL_FColor color);
    void drawRotatedRect(const SE::ObjectPtr object, SDL_FColor color);
    void drawRotatedFilledRect(const SE::ObjectPtr object, SDL_FColor color);

    void drawCircle(const SE::ObjectPtr object, SDL_FColor color);
    void drawRotatedCircle(const SE::ObjectPtr object, SDL_FColor color);
    // used to show the living objects count in the simulation
    void renderObjectCount(int count);

    bool initWindow();
    bool initRenderer();
    bool initTTF();

    // stores objects with a corresponding color
    std::unordered_map<SE::ObjectPtr, SDL_FColor> m_renderMap;

    const Settings& m_settings;

    SDL_Window* m_window;       // window
    SDL_Renderer* m_renderer;   // renderer
    TTF_Font* m_font;           // font
    SDL_Surface* m_text;        // font surface
    SDL_Color m_textColor;      // text color
    SDL_Texture* m_textTexture; // text texture
};
