#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include <cmath>
#include <iostream>
#include "colour.hh"

enum PieceNames
{
    nKing = 'K',
    nQueen = 'Q',
    nRook = 'R',
    nBishop = 'B',
    nKnight = 'N',
    nPawn = 'P'
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

class Piece
{
    private:
        Colour colour;
        char name;
        int value;
        int moveCount = 0;
    public:
        Piece();
        Piece(Colour colour, char name, int value);
        Colour getColour() {return colour;};
        char getName() {return name;};
        int getValue() {return value;};
        int getMoveCount() {return moveCount;};
        void incrementMoveCount() {moveCount++;};

        virtual ~Piece() {};
        virtual int checkMove(int src_x, int src_y, int dst_x, int dst_y) {return 1;};
        virtual int checkCapture(int src_x, int src_y, int dst_x, int dst_y) {return this->checkMove(src_x, src_y, dst_x, dst_y);};
        virtual int **generatePath(int src_x, int src_y, int dst_x, int dst_y, int *pathCount) {return nullptr;};
};

class King : public Piece
{
    public:
        King(Colour c) : Piece(c, nKing, vKing) {}
        int checkMove(int src_x, int src_y, int dst_x, int dst_y);
        int **generatePath(int src_x, int src_y, int dst_x, int dst_y, int *pathCount);
};

class Queen : public Piece
{
    public:
        Queen(Colour c) : Piece(c, nQueen, vQueen) {}
        int checkMove(int src_x, int src_y, int dst_x, int dst_y);
        int **generatePath(int src_x, int src_y, int dst_x, int dst_y, int *pathCount);
};

class Rook : public Piece
{
    public:
        Rook(Colour c) : Piece(c, nRook, vRook) {}
        int checkMove(int src_x, int src_y, int dst_x, int dst_y);
        int **generatePath(int src_x, int src_y, int dst_x, int dst_y, int *pathCount);
};

class Bishop : public Piece
{
    public:
        Bishop(Colour c) : Piece(c, nBishop, vBishop) {}
        int checkMove(int src_x, int src_y, int dst_x, int dst_y);
        int **generatePath(int src_x, int src_y, int dst_x, int dst_y, int *pathCount);
};

class Knight : public Piece
{
    public:
        Knight(Colour c) : Piece(c, nKnight, vKnight) {}
        int checkMove(int src_x, int src_y, int dst_x, int dst_y);
        int **generatePath(int src_x, int src_y, int dst_x, int dst_y, int *pathCount);
};

class Pawn : public Piece
{
    public:
        Pawn(Colour c) : Piece(c, nPawn, vPawn) {}
        int checkMove(int src_x, int src_y, int dst_x, int dst_y);
        int checkCapture(int src_x, int src_y, int dst_x, int dst_y);
        int **generatePath(int src_x, int src_y, int dst_x, int dst_y, int *pathCount);
};

#endif // CHESS_PIECE_H
