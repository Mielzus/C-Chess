#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include <iostream>
#include "colour.hh"

enum PieceValues
{
    vKing = 0,
    vQueen = 9,
    vRook = 5,
    vBishop = 3,
    vKnight = 3,
    vPawn = 1
};

class Piece
{
    private:
        Colour colour;
        char name;
        int value;
    public:
        Piece();
        Piece(Colour colour, char name, int value);
        Colour getColour() {return colour;};
        char getName() {return name;};
        int getValue() {return value;};

        virtual int checkMove(int src_x, int src_y, int dst_x, int dst_y) {return 1;};
};

// TODO Implement inherited classes for each piece

class King : public Piece
{
    public:
        King(Colour c) : Piece(c, 'K', vKing) {}
        int checkMove(int src_x, int src_y, int dst_x, int dst_y);
};

class Queen : public Piece
{
    public:
        Queen(Colour c) : Piece(c, 'Q', vQueen) {}
        int checkMove(int src_x, int src_y, int dst_x, int dst_y);
};

class Rook : public Piece
{
    public:
        Rook(Colour c) : Piece(c, 'R', vRook) {}
        int checkMove(int src_x, int src_y, int dst_x, int dst_y);
};

class Bishop : public Piece
{
    public:
        Bishop(Colour c) : Piece(c, 'B', vBishop) {}
        int checkMove(int src_x, int src_y, int dst_x, int dst_y);
};

class Knight : public Piece
{
    public:
        Knight(Colour c) : Piece(c, 'N', vKnight) {}
        int checkMove(int src_x, int src_y, int dst_x, int dst_y);
};

class Pawn : public Piece
{
    public:
        Pawn(Colour c) : Piece(c, 'P', vPawn) {}
        int checkMove(int src_x, int src_y, int dst_x, int dst_y);
};

#endif // CHESS_PIECE_H
