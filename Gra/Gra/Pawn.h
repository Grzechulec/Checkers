#pragma once
#include <vector>

#include "Piece.h"
class Pawn :
    public Piece
{
private:
    //bool fileExists(int x, int y);
public:
    Pawn(Tile * tilePtr);
    Pawn();
    ~Pawn();

    //bool canCapture(Board board);

};

