#include "colour.hh"

Colour::Colour()
{
    
}

Colour::Colour(char c)
{
    colour = c;

    if (colour == COLOUR_BLACK) {
        name = "Black";
    } else {
        name = "White";
    }
}