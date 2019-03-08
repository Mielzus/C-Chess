#include "player.hh"

Player::Player(Colour c)
{
    colour = c;
    score = 0;
    setName(c.getColourName());
}

Player::Player(Colour c, char *n)
{
    colour = c;
    score = 0;
    setName(n);
}

void Player::setName(const char *n)
{
    name = (char*) malloc(strlen(n) * sizeof(char));
    strcpy(name, n);
}

void Player::addScore(int s)
{
    score += s;
}

void Player::addPiece(char p)
{
    capturedPieces.push_back(p);
}

void Player::print()
{
    std::cout << name << ": " << score << "\t";
    for (int i = 0, s = capturedPieces.size(); i < s; i++) {
        std::cout << colour.getColour() << capturedPieces[i] << " ";
    }
    std::cout << std::endl;
}