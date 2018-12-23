#include "player.hh"

Player::Player()
{
    
}

Player::Player(Colour c)
{
    colour = c;
}

Player::Player(Colour c, char *n)
{
    colour = colour;
    setName(n);
}

void Player::setName(char *n)
{
    name = (char*) malloc(strlen(n) * sizeof(char));
    strcpy(name, n);
}

void Player::print()
{
    
}