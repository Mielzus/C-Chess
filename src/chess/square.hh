#ifndef CHESS_SQUARE_H
#define CHESS_SQUARE_H

#include <iostream>
#include "colour.hh"
#include "piece.hh"

class Square
{
    private:
        Colour colour;
        Piece *piece;
    public:
        Square();
        Square(Colour colour);
        Square(Colour colour, Piece *p);
        Colour getColour() {return colour;};
        Piece *getPiece() {return piece;};
        void setPiece(Piece *p);
};

#endif // CHESS_SQUARE_H
