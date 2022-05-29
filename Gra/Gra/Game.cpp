#include "Game.h"


//private functions
void Game::initVariables()
{
	this->window = nullptr;
}

void Game::initWindow()
{
	this->videoMode.height = 512;
	this->videoMode.width = 512;
	this->window = new sf::RenderWindow(this->videoMode, "Checkers", sf::Style::Titlebar | sf::Style::Close);
}

//checks if there's a piece on a tile
bool Game::movePossible(Tile tile, std::vector<Tile> possibleMoves)
{
	bool outcome = false;
	for (int i = 0; i < possibleMoves.size(); i++)
	{
		if (tile.getX() == possibleMoves[i].getX() && tile.getY() == possibleMoves[i].getY())
			outcome = true;
	}
	return outcome;
}

//constuctors & deconstructors
Game::Game()
{
	this->initVariables();
	this->initWindow();
}



Game::Game(int side1, int side2)
	: player1(side1), player2(side2)
{
	this->initVariables();
	this->initWindow();
	this->piecesInit();
	turn = 1;
}

void Game::helpCalculate(std::vector<Game>& vec, int index)
{
	Game* temp;
	for (int j = 0; j < player1.possibleCaptures(this->board, (*this->player1.getPiece(index))).size(); j++)
	{
		temp = new Game;
		temp = this;
		temp->player1.capture(temp->board, (*temp->player1.getPiece(index)),
			&temp->player1.possibleCaptures(board, (*temp->player1.getPiece(index)))[j], temp->player2);
		if (temp->player1.canCapture(temp->board, (*temp->player1.getPiece(index))))
			helpCalculate(vec, index);
		else
			vec.push_back(*temp);
	}
}

Game::~Game()
{
	//delete this->window;
}


//accessors
const bool Game::isRunning() const
{
	return this->window->isOpen();
}



//public functions

void Game::piecesInit()
{
	Pawn* newPawn1;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if ((i + j) % 2 == 0)
			{
				newPawn1 = new Pawn(&this->board.tile[i][j]);
				newPawn1->setValue(-1);
				this->board.tile[i][j].piecePtr = newPawn1;
				this->player2.pieces.push_back(newPawn1);
				//this->board.tile[i][j].piecePtr = &this->player2.pieces.back();
			}
		}
	}
	Pawn* newPawn2;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 5; j < 8; j++)
		{
			if ((i + j) % 2 == 0)
			{
				newPawn2 = new Pawn(&this->board.tile[i][j]);
				newPawn2->setValue(1);
				this->board.tile[i][j].piecePtr = newPawn2;
				this->player1.pieces.push_back(newPawn2);
				//this->board.tile[i][j].piecePtr = &this->player1.pieces.back();
			}
		}
	}
	//player1.printPiecesPositions();
}


std::vector<Game> Game::allPossibleMoves()
{
	Game* temp;
	std::vector<Game> outcome;
	if (this->turn == 1)
	{
		if (this->player1.hasAnyCapture(this->board))
		{
			outcome = calculateAllCaptures();
		}
		else
		{
			for (int i = 0; i < this->player1.pieces.size(); i++)
			{
				for (int j = 0; j < this->player1.possibleRegularMoves(this->board, *this->player1.getPiece(i)).size(); j++)
				{
					temp = new Game;
					temp = this;
					temp->player1.makeMove(temp->board, *temp->player1.getPiece(i),
						&temp->player1.possibleRegularMoves(this->board, *this->player1.getPiece(i))[j]);
					outcome.push_back(*temp);
				}
			}
		}
	}
	return outcome;
}

std::vector<Game> Game::calculateAllCaptures()
{
	Game* temp;
	std::vector<Game> outcome;
	if (this->turn == 1)
	{
		for (int i = 0; i < player1.pieces.size(); i++)
		{
			if (player1.canCapture(this->board, (*player1.getPiece(i))))
			{
				for (int j = 0; j < player1.possibleCaptures(this->board, (*this->player1.getPiece(i))).size(); j++)
				{
					temp = new Game;
					temp = this;
					temp->player1.capture(temp->board, (*temp->player1.getPiece(i)), 
						&temp->player1.possibleCaptures(board, (*temp->player1.getPiece(i)))[j], temp->player2);
					if (temp->player1.canCapture(temp->board, (*temp->player1.getPiece(i))))
						helpCalculate(outcome, i);
					else
						outcome.push_back(*temp);
				}
			}
		}
	}
	return outcome;
}

void Game::gameLogic(Player& player, Player& enemy)
{
	sf::Vector2i position;
	position = sf::Mouse::getPosition(*this->window);
	position = position / 64;
	//std::cout << this->allPossibleMoves().size();

	if (this->board.tile[position.x][position.y].isOcupied() && this->board.tile[position.x][position.y].piecePtr->getValue() * player.getSide() > 0 && nextCapture == 0)
	{
		//std::cout << this->board.tile[position.x][position.y].isOcupied();
		if (!player.hasAnyCapture(this->board))
		{
			possibleMoves = player.possibleRegularMoves(this->board, this->board.tile[position.x][position.y].piecePtr);
			//std::cout << "a";
		}
		else
		{
			possibleMoves = player.possibleCaptures(this->board, this->board.tile[position.x][position.y].piecePtr);
			//std::cout << "b";
		}
		this->piecePosition = position;
	}
	if (this->movePossible(this->board.tile[position.x][position.y], this->possibleMoves) && !player.canCapture(this->board, this->board.tile[piecePosition.x][piecePosition.y].piecePtr) && nextCapture == 0)
	{
		player.makeMove(this->board, this->board.tile[piecePosition.x][piecePosition.y].piecePtr, &this->board.tile[position.x][position.y]);
		possibleMoves.clear();
		this->turn *= -1;

	}
	if (this->movePossible(this->board.tile[position.x][position.y], this->possibleMoves) && player.canCapture(this->board, this->board.tile[piecePosition.x][piecePosition.y].piecePtr))
	{
		player.capture(this->board, this->board.tile[piecePosition.x][piecePosition.y].piecePtr, &this->board.tile[position.x][position.y],enemy);
		possibleMoves.clear();
		piecePosition = position;


		if (player.canCapture(this->board, this->board.tile[piecePosition.x][piecePosition.y].piecePtr))
		{
			nextCapture = 1;
			possibleMoves = player.possibleCaptures(this->board, this->board.tile[piecePosition.x][piecePosition.y].piecePtr);
		}
		else
		{
			nextCapture = 0;
			this->turn *= -1;
		}
	}

}

void Game::UpdateEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		if (this->ev.type == sf::Event::Closed)
		{
			this->window->close();
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			//std::cout << turn;
			if(turn == 1)
				gameLogic(player1, player2);
			if(turn == -1)
				gameLogic(player2, player1);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		{
			player2.printPiecesPositions();
		}
	}
}



void Game::update()
{
	this->UpdateEvents();

}



void Game::render()
{
	this->window->clear(sf::Color::White);
	
	this->board.draw(this->window);
	this->player1.drawPieces(this->window, board);
	this->player2.drawPieces(this->window, board);
	this->player1.showPossibleMoves(this->possibleMoves, this->window);
	this->player2.showPossibleMoves(this->possibleMoves, this->window);

	this->window->display();
}
