#include "game.hpp"

int main() {
    Game game = Game();
    game.start();
    // SE::Packet packet("hello");
    // NetworkClient client = NetworkClient();
    // client.startClient();
    // if (client.connectToServer()) {
    //     client.sendPacketToServer(packet);
    //     std::cout << "Packet sent. Waiting for server response...\n";
    //     std::cin.get(); // Pause to keep the client alive
    // }

    return 0;
}
