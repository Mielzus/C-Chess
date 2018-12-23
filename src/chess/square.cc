#include "square.hh"

Square::Square()
{
    
}

Square::Square(int v, int h, Colour c)
{
    x = h;
    y = v;
    colour = c;
    piece = nullptr;
}

Square::Square(int v, int h, Colour c, Piece *p)
{
    x = h;
    y = v;
    colour = c;
    piece = p;
}

void Square::setPiece(Piece *p)
{
    piece = p;
}
