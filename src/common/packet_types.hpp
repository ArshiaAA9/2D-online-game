#pragma once

enum PacketType {
    PLAYER_POS,
    TEST,
};

struct Packet {
    int test1, test2, test3;
    PacketType type = TEST;
};
