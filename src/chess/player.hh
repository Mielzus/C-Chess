#ifndef CHESS_PLAYER_H
#define CHESS_PLAYER_H

#include <iostream>
#include <string.h>
#include "colour.hh"

class Player
{
    private:
        Colour colour;
        char *name;
        int score;
    public:
        Player();
        Player(Colour colour);
        Player(Colour colour, char *name);
        Colour getColour() {return colour;};
        char *getName() {return name;};
        int getScore() {return score;};
        void setName(char *name);
        void print();
};

#endif // CHESS_PLAYER_H