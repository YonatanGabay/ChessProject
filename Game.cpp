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
			this->_board[i][j] = makeCessman(board[k++]);

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
	return "";
}

bool Game::hasChessman(string place)
{
	return "";
}

char Game::win()
{
	return 'h';
}

bool Game::isShah(char player)
{
	return false;
}
bool Game::isFreePath(string movement)
{
	return "";
}

void Game::changePlace(string movement)
{

}

Chessman* Game::makeCessman(char type)
{
	return NULL;
}

void Game::printBoard()
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
			cout << this->_board[i][j]->getType() << " ";
		cout << endl;
	}
}
