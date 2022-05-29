#pragma once

#include<iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Board.h"
#include "Player.h"

/*
	Wrapper class
*/
class Game
{
private:

	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;
	
	int turn;
	Board board;
	Player player1;
	Player player2;
	std::vector<Tile> possibleMoves;
	sf::Vector2i piecePosition;
	bool nextCapture = 0;

	void initVariables();
	void initWindow();
	void helpCalculate(std::vector<Game>& vec, int index);

	bool movePossible(Tile tile, std::vector<Tile> possibleMoves);
public:
	//constructors & deconstructors
	Game();
	Game(int side1, int side2);
	virtual ~Game();

	//accessors
	const bool isRunning() const;

	//functions
	std::vector<Game> allPossibleMoves();
	std::vector<Game> calculateAllCaptures();
	void gameLogic(Player& player, Player& enemy);
	void piecesInit();
	void UpdateEvents();
	void update();
	void render();
};