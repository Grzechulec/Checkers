#pragma once

#include "Piece.h"

class Piece;
class Tile;

class Tile
{
private:
	int x = 999;
	int y = 999;
public:
	Tile();
	~Tile();
	void setX(int x);
	void setY(int y);
	int getX();
	int getY();
	Piece* piecePtr;
	const bool isOcupied() const;
};

