#ifndef CHESS_PLAYER_H
#define CHESS_PLAYER_H

#include <cstring>
#include <iostream>
#include <vector>
#include "colour.hh"

class Player
{
    private:
        Colour colour;
        char *name;
        int score;
        std::vector<char> capturedPieces;
    public:
        Player();
        Player(Colour colour);
        Player(Colour colour, char *name);
        Colour getColour() {return colour;};
        char *getName() {return name;};
        int getScore() {return score;};
        void setName(const char *name);
        void addScore(int score);
        void addPiece(char piece);
        void print();
};

#endif // CHESS_PLAYER_H