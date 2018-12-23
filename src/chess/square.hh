#ifndef CHESS_SQUARE_H
#define CHESS_SQUARE_H

#include <iostream>
#include "colour.hh"
#include "piece.hh"

class Square
{
    private:
        int x;
        int y;
        Colour colour;
        Piece *piece;
    public:
        Square();
        Square(int x, int y, Colour colour);
        Square(int x, int y, Colour colour, Piece *p);
        int getX() {return x;};
        int getY() {return y;};
        Colour getColour() {return colour;};
        Piece *getPiece() {return piece;};
        void setPiece(Piece *p);
};

#endif // CHESS_SQUARE_H
