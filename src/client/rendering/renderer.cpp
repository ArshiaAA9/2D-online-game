#include "renderer.hpp"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

#include "SDL3_ttf/SDL_ttf.h"

std::pair<int, int> SM::Renderer::readWidthHeight() {
    using json = nlohmann::json;
    std::ifstream file("../config/settings.json");
    json settings = json::parse(file)["client"]["settings"];
    // reads the file with fstream and parses it into a object
    // TODO: maby move this to constructor of game and make it a member ?
    try {
        int width = settings["width"];
        int height = settings["height"];
        std::cout << "width: " << width << " height: " << height << '\n';
        return std::pair<int, int>{width, height};
    } catch (...) {
        std::cerr << "unable to read settings.json! using defaults\n";
        int width = settings["defaults"]["width"];
        int height = settings["defaults"]["height"];
        std::cout << "width: " << width << " height: " << height << '\n';
        return std::pair<int, int>{width, height};
    }
}

void SM::Renderer::init() {
    // main init function
    // checks if everything is initialized correctly
    if (!initTTF()) {
        std::cerr << "something went wrong!\n";
    }
    // set renderer color and clear window
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    SDL_RenderClear(m_renderer);
}

/*these functions are used in Renderer::init() to initalize the
 *different part of the renderer
 */
bool SM::Renderer::initTTF() {
    // initialize font
    if (!TTF_Init()) {
        std::cerr << "Error initializing TTF" << SDL_GetError() << std::endl;
        return false;
    }
    // set the font
    m_font = TTF_OpenFont("../config/fonts/Comic_Neue/ComicNeue-Regular.ttf", 24);
    if (!m_font) {
        std::cerr << "Failed to load font: " << SDL_GetError() << std::endl;
    }
    return true;
}

bool SM::Renderer::initRenderer() {
    // create window
    auto widthHeight = readWidthHeight();
    m_window = SDL_CreateWindow("Physics Simulation", widthHeight.first, widthHeight.second, 0);
    if (!m_window) {
        std::cerr << "Error creating window: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

bool SM::Renderer::initWindow() {
    // create renderer
    m_renderer = SDL_CreateRenderer(m_window, nullptr);
    if (!m_renderer) {
        std::cerr << "Error creating renderer: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}
