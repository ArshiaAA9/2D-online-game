#include "game/game.hpp"
#include "rendering/renderer.hpp"

namespace SM {

int main() {
    Game game = Game();
    game.run();
    Renderer renderer = Renderer();
    renderer.init();

    return 0;
}
} // namespace SM
