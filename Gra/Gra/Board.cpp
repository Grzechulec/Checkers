#include <iostream>

#include "Board.h"

Board::Board()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			tile[i][j].setX(i);
			tile[i][j].setY(j);
		}
	}
}

void Board::draw(sf::RenderWindow * window)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			sf::RectangleShape rect(sf::Vector2f(64, 64));
			sf::Uint8 c = ((i + j) % 2) * 255;
			rect.setFillColor(sf::Color(c, c, c));
			rect.setPosition(sf::Vector2f((float)i*64.f,(float)j*64.f));
			window->draw(rect);
		}
	}
}

