#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

#include "Piece.h"
#include "Tile.h"


class Board
{
private:

public:
	Board();
	Tile tile[8][8];
	void draw(sf::RenderWindow * window);
};

