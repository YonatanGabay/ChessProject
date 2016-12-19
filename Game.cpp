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


Game::Game(char turn, string board)
{
	int k = 0;

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			this->_board[i][j] = makeCessman(board[k++], convertPlace(i, j));
		}
	}

}
Game::~Game()
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (this->_board[i][j] != NULL)
			{
				delete this->_board[i][j];
			}
		}
	}
}

string Game::move(string movement)
{
	// need to do
	return NULL;
}

char Game::hasChessman(string place)
{
	char toRet = NULL;
	if (_board[BOARD_SIZE - (place.at(1) - VALUE_1)][place.at(0) - VALUE_a] != NULL)
	{
		toRet = _board[BOARD_SIZE - (place.at(1) - VALUE_1)][place.at(0) - VALUE_a]->getType();
	}
	return toRet;
}

char Game::win()
{
	// need to do
	return NULL;
}

bool Game::isShah(char player)
{
	string kingPlace = getKingPlace(player);
	bool shah = false;

	// need to add

	shah = shahRook(kingPlace, player);

	return NULL;
}

bool Game::isFreePath(string movement)
{
	bool check = true;
	string place = "";
	for (int i = 0; i < movement.length(); i += 2)
	{
		place = movement.at(i);
		place += movement.at(i + 1);
		if (hasChessman(place))
		{
			check = false;
		}
	}
	return check;;
}

void Game::changePlace(string movement) //movement: "abcd", ab= sorce place, cd= destination place
{
	Chessman* temp = _board[BOARD_SIZE - (movement.at(1) - VALUE_1)][movement.at(0) - VALUE_a]; //save the chessman to move
	_board[BOARD_SIZE - (movement.at(1) - VALUE_1)][movement.at(0) - VALUE_a] = NULL; //empy the sorce place
	if (_board[BOARD_SIZE - (movement.at(3) - VALUE_1)][movement.at(2) - VALUE_a]) //eat the chessman in destination place if there is, Yummi!!
	{
		delete _board[BOARD_SIZE - (movement.at(3) - VALUE_1)][movement.at(2) - VALUE_a];
	}
	_board[BOARD_SIZE - (movement.at(3) - VALUE_1)][movement.at(02) - VALUE_a] = temp; //save in destination place the chessman
}

Chessman* Game::makeCessman(char type, string place)
{
	Chessman* chessman = NULL;

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

	i = 8 - i; // make at board numbers

			   // set place with ascii
	place[0] = (char)(j + VALUE_a);
	place[1] = (char)(i + VALUE_1 - 1);

	return place;
}

string Game::getKingPlace(char player)
{
	string place = "";

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if ((player == WITE && _board[i][j]->getType() == KING_W) || (player == WITE && _board[i][j]->getType() == KING_W))
			{
				place = convertPlace(i, j);
				break;
			}
		}
		if (!place.empty())
		{
			break;
		}
	}

	return place;
}

bool Game::shahRook(string kingPlace, char player)
{
	int j = (int)kingPlace.at(0) - VALUE_a;
	int i = (int)kingPlace.at(1) - VALUE_1 + 1;
	bool isShah = false;

	for (i = i; i < BOARD_SIZE; i++)
	{
		if (_board[i][j])
		{
			if ((_board[i][j]->getType() == KING_B && player == BLACK) || (_board[i][j]->getType() == KING_W && player == WITE))
			{
				isShah = true;
			}
			break;
		}
	}

	i = (int)kingPlace.at(1) - VALUE_1 + 1;

	for (j = j; j < BOARD_SIZE; j++)
	{
		if (_board[i][j])
		{
			if ((_board[i][j]->getType() == KING_B && player == BLACK) || (_board[i][j]->getType() == KING_W && player == WITE))
			{
				isShah = true;
			}
			break;
		}
	}

	return isShah;
}

