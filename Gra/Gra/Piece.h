#pragma once

#include "Tile.h"
#include <iostream>

class Tile;
class Piece;


class Piece
{
protected:
	int value;
public:
	Tile* tilePtr;
	//constructor & deconstructor
	Piece();
	~Piece();

	//public functions
	int getValue();
	void setValue(int value);
	//void showMoves();
};

