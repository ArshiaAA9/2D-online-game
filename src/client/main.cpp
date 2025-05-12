#include "../common/packet_types.hpp"
#include "game/game.hpp"
#include "networking/network_client.hpp"

int main() {
    //    Game game = Game();
    //    game.start();
    Packet packet = {1, 1, 1, TEST};
    NetworkClient client = NetworkClient();
    client.startClient();
    if (client.connectToServer()) {
        client.sendPacketToServer(packet);
        std::cout << "Packet sent. Waiting for server response...\n";
        std::cin.get(); // Pause to keep the client alive
    }

    return 0;
}
