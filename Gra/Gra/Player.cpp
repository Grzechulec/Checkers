#include <iostream>

#include "Player.h"

Player::Player(int side)
{
	this->side = side;
	piece = nullptr;
	pieces.clear();
	//this->pieces.reserve(12);
}

Player::Player()
{
	this->side = 0;
	piece = nullptr;
}


int Player::getSide()
{
	return this->side;
}

bool Player::tileExists(int x, int y)
{
	if (x >= 0 && x <= 7 && y >= 0 && y <= 7)
		return true;
	else
		return false;
}


void Player::drawPieces(sf::RenderWindow* window, Board& board)
{
	for (int i = 0; i < pieces.size(); i++)
	{
		sf::CircleShape element(16.f);
		//Piece piece = *this->getPiece(i);
		switch ((*getPiece(i))->getValue())
		{
		case 1:
			element.setFillColor(sf::Color(0, 255, 0));
			break;
		case 2:
			element.setFillColor(sf::Color(0, 255, 0));
			element.setOutlineThickness(4.f);
			element.setOutlineColor(sf::Color(255, 255, 255));
			break;
		case -1:
			element.setFillColor(sf::Color(255, 0, 0));
			break;
		case -2:
			element.setFillColor(sf::Color(255, 0, 0));
			element.setOutlineThickness(4.f);
			element.setOutlineColor(sf::Color(255, 255, 255));
			break;
		default:
			std::cout << "*************";
			break;
		}

		float x = (float)(*getPiece(i))->tilePtr->getX() * 64.f + 16.f;
		float y = (float)(*getPiece(i))->tilePtr->getY() * 64.f + 16.f;
		element.setPosition(sf::Vector2f(x, y));
		window->draw(element);

	}
}

void Player::makeMove(Board& board, Piece* piece, Tile* newPosition)
{
	piece->tilePtr->piecePtr = nullptr;
	piece->tilePtr = newPosition;
	newPosition->piecePtr = piece;
	if (piece->tilePtr->getY() == 0 && piece->getValue() == 1)
		promotion(piece);
	if (piece->tilePtr->getY() == 7 && piece->getValue() == -1)
		promotion(piece);
}

bool Player::hasAnyCapture(Board& board)
{
	for (int i = 0; i < this->pieces.size(); i++)
	{
		if (this->canCapture(board, *this->getPiece(i)))
		{
			//std::cout << this->getPiece(i).tilePtr->getX() << " " << this->getPiece(i).tilePtr->getY();
			return true;
		}
	}
	return false;
}

std::vector<Tile> Player::possibleCaptures(Board& board, Piece* piece)
{
	std::vector<Tile> outcome;
	Tile* temp;
	int x = piece->tilePtr->getX();
	int y = piece->tilePtr->getY();
	if (piece->getValue() == 1 || piece->getValue() == -1)
	{
		if (tileExists(x - 1, y - 1) && board.tile[x - 1][y - 1].isOcupied() && this->side * board.tile[x - 1][y - 1].piecePtr->getValue() < 0)
		{
			if (tileExists(x - 2, y - 2) && !(board.tile[x - 2][y - 2].isOcupied()))
			{
				temp = new Tile;
				temp->setX(x - 2);
				temp->setY(y - 2);
				outcome.push_back(*temp);
			}

		}
		if (tileExists(x + 1, y - 1) && board.tile[x + 1][y - 1].isOcupied() && this->side * board.tile[x + 1][y - 1].piecePtr->getValue() < 0)
		{
			if (tileExists(x + 2, y - 2) && !(board.tile[x + 2][y - 2].isOcupied()))
			{
				temp = new Tile;
				temp->setX(x + 2);
				temp->setY(y - 2);
				outcome.push_back(*temp);
			}
		}
		if (tileExists(x - 1, y + 1) && board.tile[x - 1][y + 1].isOcupied() && this->side * board.tile[x - 1][y + 1].piecePtr->getValue() < 0)
		{
			if (tileExists(x - 2, y + 2) && !(board.tile[x - 2][y + 2].isOcupied()))
			{
				temp = new Tile;
				temp->setX(x - 2);
				temp->setY(y + 2);
				outcome.push_back(*temp);
			}
		}
		if (tileExists(x + 1, y + 1) && board.tile[x + 1][y + 1].isOcupied() && this->side * board.tile[x + 1][y + 1].piecePtr->getValue() < 0)
		{
			if (tileExists(x + 2, y + 2) && !(board.tile[x + 2][y + 2].isOcupied()))
			{
				temp = new Tile;
				temp->setX(x + 2);
				temp->setY(y + 2);
				outcome.push_back(*temp);
			}
		}
	}
	if (piece->getValue() == 2 || piece->getValue() == -2)
	{
		sf::Vector2i direction = { 1, 1 };
		sf::Vector2i pos = { piece->tilePtr->getX(), piece->tilePtr->getY() };
		pos += direction;
		while (this->tileExists(pos.x, pos.y) && !board.tile[pos.x][pos.y].isOcupied())
		{
			pos += direction;
		}
		if (this->tileExists(pos.x, pos.y) && board.tile[pos.x][pos.y].piecePtr->getValue() * piece->getValue() < 0)
		{
			pos += direction;
			while (this->tileExists(pos.x, pos.y) && !board.tile[pos.x][pos.y].isOcupied())
			{
				temp = new Tile;
				temp->setX(pos.x);
				temp->setY(pos.y);
				outcome.push_back(*temp);
				pos += direction;
			}
		}

		direction = { 1, -1 };
		pos = { piece->tilePtr->getX(), piece->tilePtr->getY() };
		pos += direction;
		while (this->tileExists(pos.x, pos.y) && !board.tile[pos.x][pos.y].isOcupied())
		{
			pos += direction;
		}
		if (this->tileExists(pos.x, pos.y) && board.tile[pos.x][pos.y].piecePtr->getValue() * piece->getValue() < 0)
		{
			pos += direction;
			while (this->tileExists(pos.x, pos.y) && !board.tile[pos.x][pos.y].isOcupied())
			{
				temp = new Tile;
				temp->setX(pos.x);
				temp->setY(pos.y);
				outcome.push_back(*temp);
				pos += direction;
			}
		}

		direction = { -1, 1 };
		pos = { piece->tilePtr->getX(), piece->tilePtr->getY() };
		pos += direction;
		while (this->tileExists(pos.x, pos.y) && !board.tile[pos.x][pos.y].isOcupied())
		{
			pos += direction;
		}
		if (this->tileExists(pos.x, pos.y) && board.tile[pos.x][pos.y].piecePtr->getValue() * piece->getValue() < 0)
		{
			pos += direction;
			while (this->tileExists(pos.x, pos.y) && !board.tile[pos.x][pos.y].isOcupied())
			{
				temp = new Tile;
				temp->setX(pos.x);
				temp->setY(pos.y);
				outcome.push_back(*temp);
				pos += direction;
			}
		}

		direction = { -1, -1 };
		pos = { piece->tilePtr->getX(), piece->tilePtr->getY() };
		pos += direction;
		while (this->tileExists(pos.x, pos.y) && !board.tile[pos.x][pos.y].isOcupied())
		{
			pos += direction;
		}
		if (this->tileExists(pos.x, pos.y) && board.tile[pos.x][pos.y].piecePtr->getValue() * piece->getValue() < 0)
		{
			pos += direction;
			while (this->tileExists(pos.x, pos.y) && !board.tile[pos.x][pos.y].isOcupied())
			{
				temp = new Tile;
				temp->setX(pos.x);
				temp->setY(pos.y);
				outcome.push_back(*temp);
				pos += direction;
			}
		}
	}
	return outcome;
}

void Player::showPossibleMoves(std::vector<Tile>& moves, sf::RenderWindow* window)
{

	sf::CircleShape shape(8.f);
	shape.setFillColor(sf::Color::Yellow);
	for (int i = 0; i < moves.size(); i++)
	{
		float x = (float)moves[i].getX() * 64.f + 24.f;
		float y = (float)moves[i].getY() * 64.f + 24.f;
		shape.setPosition(sf::Vector2f(x, y));
		window->draw(shape);
	}
}

void Player::capture(Board& board, Piece* piece, Tile* newTile, Player& enemy)
{
	Tile* temp = piece->tilePtr;
	std::list<Piece*>::iterator iter = this->pieces.begin();

	int directionX = temp->getX() - newTile->getX();
	if (directionX > 0)
		directionX = -1;
	else
		directionX = 1;

	int directionY = temp->getY() - newTile->getY();
	if (directionY > 0)
		directionY = -1;
	else
		directionY = 1;

	temp = &board.tile[temp->getX() + directionX][temp->getY() + directionY];
	while (temp != newTile)
	{
		if (temp->isOcupied())
		{
			iter = findPiece(temp->getX(), temp->getY(), enemy);
			delete *iter;
			enemy.pieces.erase(iter);
			//delete board.tile[temp->getX(), temp->getY()]->piecePtr;
		}
		//std::cout << temp->getX() << temp->getY() << "   " << newTile->getX() << newTile->getY() << std::endl;
		temp = &board.tile[temp->getX() + directionX][temp->getY() + directionY];
	}
	makeMove(board, piece, newTile);
}

void Player::printPiecesPositions()
{
	for (int i = 0; i < this->pieces.size(); i++)
	{
		std::cout << (*getPiece(i))->tilePtr->getX() << "  " << (*getPiece(i))->tilePtr->getY() << std::endl;
	}
	std::cout << std::endl;
}

std::list<Piece*>::iterator Player::findPiece(int x, int y, Player& enemy)
{
	std::list<Piece*>::iterator outcome = enemy.pieces.begin();
	int i = 0;
	while (!((*enemy.getPiece(i))->tilePtr->getX() == x && (*enemy.getPiece(i))->tilePtr->getY() == y))
	{
		i++;
		outcome++;
	}
	//std::cout << i;
	return outcome;
}

std::list<Piece*>::iterator Player::getPiece(int index)
{
	std::list<Piece*>::iterator it = this->pieces.begin();
	for (int i = 0; i < index; i++)
	{
		++it;
	}

	return it;
}

void Player::promotion(Piece* piece)
{
	piece->setValue(piece->getValue() * 2);
}

std::vector<Tile> Player::possibleRegularMoves(Board& board, Piece* piece)
{
	std::vector<Tile> outcome;
	Tile* temp;
	int x = piece->tilePtr->getX();
	int y = piece->tilePtr->getY();
	if (piece->getValue() == 1 || piece->getValue() == -1)
	{
		//std::cout << this->tileExists(x - 1, y - this->side) << " " << !board.tile[x - 1][y - this->side].isOcupied() <<std::endl;
		if (this->tileExists(x - 1, y - this->side) && !board.tile[x - 1][y - this->side].isOcupied())
		{
			temp = new Tile;
			temp->setX(x - 1);
			temp->setY(y - this->side);
			outcome.push_back(*temp);
		}
		if (this->tileExists(x + 1, y - this->side) && !board.tile[x + 1][y - this->side].isOcupied())
		{
			temp = new Tile;
			temp->setX(x + 1);
			temp->setY(y - this->side);
			outcome.push_back(*temp);
		}
	}
	if (piece->getValue() == 2 || piece->getValue() == -2)
	{
		sf::Vector2i direction = { 1, 1 };
		sf::Vector2i pos = { piece->tilePtr->getX(), piece->tilePtr->getY() };
		pos += direction;
		while (this->tileExists(pos.x, pos.y) && !board.tile[pos.x][pos.y].isOcupied())
		{
			temp = new Tile;
			temp->setX(pos.x);
			temp->setY(pos.y);
			outcome.push_back(*temp);
			pos += direction;
		}
		
		direction = { 1, -1 };
		pos = { piece->tilePtr->getX(), piece->tilePtr->getY() };
		pos += direction;
		while (this->tileExists(pos.x, pos.y) && !board.tile[pos.x][pos.y].isOcupied())
		{
			temp = new Tile;
			temp->setX(pos.x);
			temp->setY(pos.y);
			outcome.push_back(*temp);
			pos += direction;
		}

		direction = { -1, 1 };
		pos = { piece->tilePtr->getX(), piece->tilePtr->getY() };
		pos += direction;
		while (this->tileExists(pos.x, pos.y) && !board.tile[pos.x][pos.y].isOcupied())
		{
			temp = new Tile;
			temp->setX(pos.x);
			temp->setY(pos.y);
			outcome.push_back(*temp);
			pos += direction;
		}

		direction = { -1, -1 };
		pos = { piece->tilePtr->getX(), piece->tilePtr->getY() };
		pos += direction;
		while (this->tileExists(pos.x, pos.y) && !board.tile[pos.x][pos.y].isOcupied())
		{
			temp = new Tile;
			temp->setX(pos.x);
			temp->setY(pos.y);
			outcome.push_back(*temp);
			pos += direction;
		}

	}
	return outcome;
}

bool Player::canCapture(Board& board, Piece* piece)
{
	int x = piece->tilePtr->getX();
	int y = piece->tilePtr->getY();
	if (piece->getValue() == 1 || piece->getValue() == -1)
	{
		if (tileExists(x - 1, y - 1) && board.tile[x - 1][y - 1].isOcupied() && this->side * board.tile[x - 1][y - 1].piecePtr->getValue() < 0)
		{
			if (tileExists(x - 2, y - 2) && !(board.tile[x - 2][y - 2].isOcupied()))
				return true;
		}
		if (tileExists(x + 1, y - 1) && board.tile[x + 1][y - 1].isOcupied() && this->side * board.tile[x + 1][y - 1].piecePtr->getValue() < 0)
		{
			if (tileExists(x + 2, y - 2) && !(board.tile[x + 2][y - 2].isOcupied()))
				return true;
		}
		if (tileExists(x - 1, y + 1) && board.tile[x - 1][y + 1].isOcupied() && this->side * board.tile[x - 1][y + 1].piecePtr->getValue() < 0)
		{
			if (tileExists(x - 2, y + 2) && !(board.tile[x - 2][y + 2].isOcupied()))
				return true;
		}
		if (tileExists(x + 1, y + 1) && board.tile[x + 1][y + 1].isOcupied() && this->side * board.tile[x + 1][y + 1].piecePtr->getValue() < 0)
		{
			if (tileExists(x + 2, y + 2) && !(board.tile[x + 2][y + 2].isOcupied()))
				return true;
		}
		return false;
	}
	if (piece->getValue() == 2 || piece->getValue() == -2)
	{
		sf::Vector2i direction = { 1, 1 };
		sf::Vector2i pos = { piece->tilePtr->getX(), piece->tilePtr->getY() };
		pos += direction;
		while (this->tileExists(pos.x, pos.y) && !board.tile[pos.x][pos.y].isOcupied())
		{
			pos += direction;
		}
		if (this->tileExists(pos.x, pos.y) && board.tile[pos.x][pos.y].piecePtr->getValue() * piece->getValue() < 0)
		{
			pos += direction;
			if (this->tileExists(pos.x, pos.y) && !board.tile[pos.x][pos.y].isOcupied())
			{
				return true;
			}
		}

		direction = { 1, -1 };
		pos = { piece->tilePtr->getX(), piece->tilePtr->getY() };
		pos += direction;
		while (this->tileExists(pos.x, pos.y) && !board.tile[pos.x][pos.y].isOcupied())
		{
			pos += direction;
		}
		if (this->tileExists(pos.x, pos.y) && board.tile[pos.x][pos.y].piecePtr->getValue()*piece->getValue() < 0)
		{
			pos += direction;
			if (this->tileExists(pos.x, pos.y) && !board.tile[pos.x][pos.y].isOcupied())
			{
				return true;
			}
		}

		direction = { -1, 1 };
		pos = { piece->tilePtr->getX(), piece->tilePtr->getY() };
		pos += direction;
		while (this->tileExists(pos.x, pos.y) && !board.tile[pos.x][pos.y].isOcupied())
		{
			pos += direction;
		}
		if (this->tileExists(pos.x, pos.y) && board.tile[pos.x][pos.y].piecePtr->getValue() * piece->getValue() < 0)
		{
			pos += direction;
			if (this->tileExists(pos.x, pos.y) && !board.tile[pos.x][pos.y].isOcupied())
			{
				return true;
			}
		}

		direction = { -1, -1 };
		pos = { piece->tilePtr->getX(), piece->tilePtr->getY() };
		pos += direction;
		while (this->tileExists(pos.x, pos.y) && !board.tile[pos.x][pos.y].isOcupied())
		{
			pos += direction;
		}
		if (this->tileExists(pos.x, pos.y) && board.tile[pos.x][pos.y].piecePtr->getValue() * piece->getValue() < 0)
		{
			pos += direction;
			if (this->tileExists(pos.x, pos.y) && !board.tile[pos.x][pos.y].isOcupied())
			{
				return true;
			}
		}
		return false;
	}
	return false;
}



