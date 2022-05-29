#pragma once

#include <vector>
#include <list>

#include "Pawn.h"
#include "Queen.h"
#include "Piece.h"
#include "Board.h"



class Player
{
private:
	int side;   //-1 = black; 1 = white
	bool tileExists(int x, int y);
public:
	std::list<Piece*> pieces;
	Piece* piece;
	Player(int side);
	Player();
	int getSide();
	void drawPieces(sf::RenderWindow * window, Board& board);
	void makeMove(Board& board, Piece* piece, Tile* newPosition);
	bool canCapture(Board& board, Piece* piece);
	bool hasAnyCapture(Board& board);
	std::vector<Tile> possibleRegularMoves(Board& board, Piece* piece);
	std::vector<Tile> possibleCaptures(Board& board, Piece* piece);
	void showPossibleMoves(std::vector<Tile>& moves, sf::RenderWindow* window);
	void capture(Board& board, Piece* piece, Tile* newTile, Player& player);
	void printPiecesPositions();
	std::list<Piece*>::iterator findPiece(int x, int y, Player& enemy);
	std::list<Piece*>::iterator getPiece(int index);
	void promotion(Piece* piece);

};

