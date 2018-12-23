#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include <iostream>
#include "colour.hh"

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

        int checkMove(int src_x, int src_y, int dst_x, int dst_y);
};

// TODO Implement inherited classes for each piece

class King : public Piece
{
    public:
        King(Colour colour);
        virtual int checkMove(int src_x, int src_y, int dst_x, int dst_y);
};

class Queen : public Piece
{
    public:
        Queen(Colour colour);
        virtual int checkMove(int src_x, int src_y, int dst_x, int dst_y);
};

class Rook : public Piece
{
    public:
        Rook(Colour colour);
        virtual int checkMove(int src_x, int src_y, int dst_x, int dst_y);
};

class Bishop : public Piece
{
    public:
        Bishop(Colour colour);
        virtual int checkMove(int src_x, int src_y, int dst_x, int dst_y);
};

class Knight : public Piece
{
    public:
        Knight(Colour colour);
        virtual int checkMove(int src_x, int src_y, int dst_x, int dst_y);
};

class Pawn : public Piece
{
    public:
        Pawn(Colour colour);
        virtual int checkMove(int src_x, int src_y, int dst_x, int dst_y);
};

enum PieceValues
{
    vKing = 0,
    vQueen = 9,
    vRook = 5,
    vBishop = 3,
    vKnight = 3,
    vPawn = 1
};

#endif // CHESS_PIECE_H
