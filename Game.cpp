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

	this->_turn = board[64];

	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
			this->_board[i][j] = makeChessman(board[k++], convertPlace(i, j));

}

Game::Game(const Game& other)
{
	this->_turn = other._turn;

	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
			 if (other._board[i][j] != NULL)
				this->_board[i][j] = makeChessman(other._board[i][j]->getType(), convertPlace(i, j));
			else
				this->_board[i][j] = NULL;
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

char* Game::move(string movement)
{
	/*
	#define VALID_MOVEMENT '0'  ++
	#define SHAH_ON_OPPONENT '1'
	#define SOURCE_PLACE_INVALID '2' ++
	#define DEST_PLACE_INVALID '3'  ++
	#define SHAH_ON_HIMSELF '4'
	#define INVALID_PLACE_INDEX '5' ++
	#define INVALID_MOVEMENT '6'  ++
	#define SAME_SOURCE_AND_DEST '7'  ++

	*/
	int i, j;
	string dst = movement.substr(2, 2);
	string src = movement.substr(0, 2);
	char* toRet = new char[2];
	toRet[1] = 0;
	Chessman* temp;
	int srcLetter = (int)movement.at(0) - VALUE_a;
	int srcNum = (int)movement.at(1) - VALUE_1 + 1;
	int dstLetter = (int)movement.at(2) - VALUE_a;
	int dstNum = (int)movement.at(3) - VALUE_1 + 1;

	if (srcNum < 0 || srcNum > BOARD_SIZE || srcLetter < 0 || srcLetter > BOARD_SIZE || dstLetter < 0 || dstLetter > BOARD_SIZE || dstNum < 0 || dstNum > BOARD_SIZE)
	{
		toRet[0] = INVALID_PLACE_INDEX;
	}
	else if (isBlack(hasChessman(src)) != convertTurnToChar()) //check if in the sorce place there is a valid chessman
	{
		toRet[0] = SOURCE_PLACE_INVALID;
	}
	else
	{
		convertPlace(string(src), i, j);

		toRet[0] = _board[i][j]->validMove(movement, *this)[0];

		if (toRet[0] == VALID_MOVEMENT)
		{
			//save dst
			temp = _board[BOARD_SIZE - dstNum][dstLetter];
			//change places
			_board[BOARD_SIZE - dstNum][dstLetter] = _board[BOARD_SIZE - srcNum][srcLetter];
			_board[BOARD_SIZE - srcNum][srcLetter] = NULL;

			//check if there is shah on himself
			if (isShah(_turn))
			{
				_board[BOARD_SIZE - srcNum][srcLetter] = _board[BOARD_SIZE - dstNum][dstLetter];
				_board[BOARD_SIZE - dstNum][dstLetter] = temp;

				toRet[0] = SHAH_ON_HIMSELF;
			}

			else if (_turn == WHITE_CH)
			{
				if (isShah(BLACK_CH))
				{
					toRet[0] = SHAH_ON_OPPONENT;
				}
			}
			else if (isShah(WHITE_CH)) //if _turn == BLACK_CH
			{
				toRet[0] = SHAH_ON_OPPONENT;
			}
		}
	}

	return toRet;
}

char Game::hasChessman(string place)
{
	char toRet = NULL;
	if (_board[BOARD_SIZE - (place.at(1) - VALUE_1) - 1][place.at(0) - VALUE_a] != NULL)
	{
		toRet = _board[BOARD_SIZE - (place.at(1) - VALUE_1) - 1][place.at(0) - VALUE_a]->getType();
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

	shah = shahKing(kingPlace, player);
	if (!shah)
	{
		shah = shahPawn(kingPlace, player);
	}
	if (!shah)
	{
		shah = shahRook(kingPlace, player);
	}
	return shah;
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
	return check;
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

Chessman* Game::makeChessman(char type, string place)
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

void Game::convertPlace(string place, int& i, int& j)
{
	i = 8 - (place[0] - VALUE_a);
	j = place[1] - VALUE_1;
}

string Game::getKingPlace(char player)
{
	string place = "";

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if ((player == WHITE_CH && _board[i][j]->getType() == KING_W) || (player == WHITE_CH && _board[i][j]->getType() == KING_W))
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
			if ((_board[i][j]->getType() == KING_B && player == BLACK_CH) || (_board[i][j]->getType() == KING_W && player == WHITE_CH))
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
			if ((_board[i][j]->getType() == KING_B && player == BLACK_CH) || (_board[i][j]->getType() == KING_W && player == WHITE_CH))
			{
				isShah = true;
			}
			break;
		}
	}

	return isShah;
}

bool Game::shahKing(string kingPlace, char player)
{
	int j = (int)kingPlace.at(0) - VALUE_a;
	int i = (int)kingPlace.at(1) - VALUE_1 + 1;
	bool isShah = false;

	if (i > 0)
	{
		isShah = ((player == BLACK_CH && hasChessman(convertPlace(i - 1, j)) == KING_B) || (player == WHITE_CH && hasChessman(convertPlace(i - 1, j)) == KING_W));
	}
	if (j > 0 && !isShah)
	{
		isShah = ((player == BLACK_CH && hasChessman(convertPlace(i, j - 1)) == KING_B) || (player == WHITE_CH && hasChessman(convertPlace(i, j - 1)) == KING_W));
	}
	if (j < BOARD_SIZE && !isShah)
	{
		isShah = ((player == BLACK_CH && hasChessman(convertPlace(i, j + 1)) == KING_B) || (player == WHITE_CH && hasChessman(convertPlace(i, j + 1)) == KING_W));
	}
	if (i < BOARD_SIZE && !isShah)
	{
		isShah = ((player == BLACK_CH && hasChessman(convertPlace(i + 1, j)) == KING_B) || (player == WHITE_CH && hasChessman(convertPlace(i + 1, j)) == KING_W));
	}
	if (j > 0 && i > 0 && !isShah)
	{
		isShah = ((player == BLACK_CH && hasChessman(convertPlace(i - 1, j - 1)) == KING_B) || (player == WHITE_CH && hasChessman(convertPlace(i - 1, j - 1)) == KING_W));
	}
	if (j > 0 && i < BOARD_SIZE && !isShah)
	{
		isShah = ((player == BLACK_CH && hasChessman(convertPlace(i + 1, j - 1)) == KING_B) || (player == WHITE_CH && hasChessman(convertPlace(i + 1, j - 1)) == KING_W));
	}
	if (i > 0 && j < BOARD_SIZE && !isShah)
	{
		isShah = ((player == BLACK_CH && hasChessman(convertPlace(i - 1, j + 1)) == KING_B) || (player == WHITE_CH && hasChessman(convertPlace(i - 1, j + 1)) == KING_W));
	}
	if (j < BOARD_SIZE && i < BOARD_SIZE && !isShah)
	{
		isShah = ((player == BLACK_CH && hasChessman(convertPlace(i + 1, j + 1)) == KING_B) || (player == WHITE_CH && hasChessman(convertPlace(i + 1, j + 1)) == KING_W));
	}

	return isShah;
}

int Game::isBlack(char chessman)
{
	int ret = 0;
	const int MIN_BLACK = 97, MAX_BLACK = 122;

	if (chessman >= MIN_BLACK && chessman <= MAX_BLACK)
		ret = BLACK_CH;

	else if (chessman == NULL)
		ret = NULL;

	else
		ret = WHITE_CH;

	return ret;
}


bool Game::shahPawn(string kingPlace, char player)
{
	int j = (int)kingPlace.at(0) - VALUE_a;
	int i = (int)kingPlace.at(1) - VALUE_1 + 1;
	bool isShah = false;

	if (player == BLACK_NUM)
	{
		if (i > 0 && j > 0)
		{
			isShah = ((hasChessman(convertPlace(i - 1, j - 1)) == KING_B));
		}
		if (i > 0 && j < BOARD_SIZE && !isShah)
		{
			isShah = ((hasChessman(convertPlace(i - 1, j + 1)) == KING_B));
		}
	}
	else
	{
		if (i < BOARD_SIZE && j > 0)
		{
			isShah = ((hasChessman(convertPlace(i + 1, j - 1)) == KING_B));
		}
		if (i < BOARD_SIZE && j < BOARD_SIZE && !isShah)
		{
			isShah = ((hasChessman(convertPlace(i + 1, j + 1)) == KING_B));
		}
	}

	return isShah;
}

char Game::getTurn()
{
	return _turn;
}

char Game::convertTurnToChar()
{
	char ret = 0;
	if (_turn == WHITE_NUM)
	{
		ret = WHITE_CH;
	}
	else
	{
		ret = BLACK_CH;
	}

	return ret;
}