#include "Queen.h"


Queen::Queen(Tile* tile)
{
	value = 2;
	tilePtr = tile;
	tile->piecePtr = this;
}

Queen::~Queen()
{
	tilePtr->piecePtr = nullptr;
}