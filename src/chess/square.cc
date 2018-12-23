#include "square.hh"

Square::Square()
{
    
}

Square::Square(Colour c)
{
    colour = c;
    piece = nullptr;
}

Square::Square(Colour c, Piece *p)
{
    colour = c;
    piece = p;
}

void Square::setPiece(Piece *p)
{
    piece = p;
}
