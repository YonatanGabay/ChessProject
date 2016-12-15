#include <iostream> // input-output library
#include <string> // string library
#include "Game.h"
#include "Chessman.h"
#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"

#define BOARD_SIZE 8


Game::Game(char turn, string board)
{
	int k = 0;

	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
			this->_board[i][j] = makeCessman(board[k++], convertPlace(i, j));

}
Game::~Game()
{
	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
			if (this->_board[i][j] != NULL)
				delete this->_board[i][j];
}

string Game::move(string movement)
{
	// need to do
	return NULL;
}

bool Game::hasChessman(string place)
{
	// need to do
	return NULL;
}

char Game::win()
{
	// need to do
	return NULL;
}

bool Game::isShah(char player)
{
	// need to do
	return NULL;
}
bool Game::isFreePath(string movement)
{
	// need to do
	return NULL;
}

void Game::changePlace(string movement)
{
	// need to do
}

Chessman* Game::makeCessman(char type, string place)
{
	Chessman* chessman = NULL;

	const char QUEEN_B = 'q', KING_B = 'k', BISHOP_B = 'b', KNIGHT_B = 'n', ROOK_B = 'r', PAWN_B = 'p';
	const char QUEEN_W = 'Q', KING_W = 'K', BISHOP_W = 'B', KNIGHT_W = 'N', ROOK_W = 'R', PAWN_W = 'P';

	if (type == QUEEN_B || type == QUEEN_W)
		chessman = new Queen(type, place);

	else if (type == KING_B || type == KING_W)
		chessman = new King(type, place);

	else if (type == BISHOP_B || type == BISHOP_W)
		chessman = new Bishop(type, place);

	else if (type == KNIGHT_B || type == KNIGHT_W)
		chessman = new Knight(type, place);

	else if (type == ROOK_B || type == ROOK_W)
		chessman = new Rook(type, place);

	else if (type == PAWN_B || type == PAWN_W)
		chessman = new Pawn(type, place);

	return chessman;
}

void Game::printBoard()
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (this->_board[i][j] != NULL)
				cout << this->_board[i][j]->getType() << " ";

			else
				cout << "# ";
		}

		cout << endl;
	}
}

string Game::turn(string movement)
{
	// need to do
	return NULL;
}

string Game::convertPlace(int i, int j)
{
	string place("**");
	const int VALUE_1 = 49, VALUE_a = 97;

	i = 8 - i; // make at board numbers

	// set place with ascii
	place[0] = (char)(j + VALUE_a);
	place[1] = (char)(i + VALUE_1 - 1);

	return place;
}

