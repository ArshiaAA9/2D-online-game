#pragma once
#include <iostream>

// TODO: each client will have a player class which will read things
// like username, character skin, etc...

enum Color {
    REC,
    BLACK,
    BROWN,
    BLUE,
};

class player {
private:
    int playerId;
    std::string m_username;
    Color m_charColor;
};
