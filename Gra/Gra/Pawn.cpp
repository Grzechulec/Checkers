#include "Pawn.h"

Pawn::Pawn(Tile * tile)
{
	value = 1;
	tilePtr = tile;
	tile->piecePtr = this;
}

Pawn::Pawn()
{
	value = 1;
}

Pawn::~Pawn()
{
	//tilePtr->piecePtr = nullptr;
}

