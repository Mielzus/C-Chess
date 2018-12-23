#ifndef CHESS_COLOUR_H
#define CHESS_COLOUR_H

#define COLOUR_WHITE 'W'
#define COLOUR_BLACK 'B'

class Colour
{
    private:
        char colour;
        const char *name;
    public:
        Colour();
        Colour(char colour);
        char getColour() {return colour;};
        const char *getColourName() {return name;};
};

#endif