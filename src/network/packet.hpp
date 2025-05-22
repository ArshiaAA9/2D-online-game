#pragma once
#include <SunnyEngine/Physics.h>

#include <string>

#include "SunnyEngine/Vector2.h"

namespace SE {

enum PacketType { PLAYER_POS, ERROR, CHAT };

struct Packet {
    // base
    PacketType type;
    // chat
    std::string msg;      // used by both chat and error
    int senderPlayerId;   // chat
    int receiverPlayerId; // chat
    // world packet
    Vector2 playerPos; // world

    Packet() = default;

    // error packet constructor
    Packet(std::string error)
        : type(ERROR)
        , msg(error) {}

    // chat massage packet constructor
    Packet(std::string msg, int senderPlayerId, int receiverPlayerId)
        : type(CHAT)
        , msg(msg)
        , senderPlayerId(senderPlayerId)
        , receiverPlayerId(receiverPlayerId) {}
};

// polymorphism not good here probably
// struct ErrorPacket : public Packet {
//     std::string errorMassage;
//
//     ErrorPacket()
//         : Packet(PACKET_ERROR) {}
// };

} // namespace SE
