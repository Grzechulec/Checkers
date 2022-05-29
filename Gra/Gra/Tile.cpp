#include "Tile.h"

Tile::Tile()
{
    piecePtr = nullptr;
}

Tile::~Tile()
{
}

void Tile::setX(int x)
{
    this->x = x;
}

void Tile::setY(int y)
{
    this->y = y;
}

int Tile::getX()
{
    return this->x;
}

int Tile::getY()
{
    return this->y;
}


const bool Tile::isOcupied() const
{
    return this->piecePtr != nullptr;
}

