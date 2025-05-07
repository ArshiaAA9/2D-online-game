#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <bits/stdc++.h> // for std::pair

namespace SM {

class Renderer {
public:
    Renderer() = default;
    void init();

private:
    std::pair<int, int> readWidthHeight();

    bool initWindow();
    bool initRenderer();
    bool initTTF();

    SDL_Window* m_window;       // window
    SDL_Renderer* m_renderer;   // renderer
    TTF_Font* m_font;           // font
    SDL_Surface* m_text;        // font surface
    SDL_Color m_textColor;      // text color
    SDL_Texture* m_textTexture; // text texture
};
} // namespace SM
