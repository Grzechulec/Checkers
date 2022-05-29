#include "Piece.h"

Piece::Piece()
{
	value = 0;
	tilePtr = nullptr;
}

Piece::~Piece()
{
	tilePtr->piecePtr = nullptr;
	tilePtr = nullptr;
}


int Piece::getValue()
{
	return this->value;
}

void Piece::setValue(int value)
{
	this->value = value;
}
