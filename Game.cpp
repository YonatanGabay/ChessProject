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
	int i, j;
	string dst = movement.substr(2, 2);
	string src = movement.substr(0, 2);
	char* toRet = new char[2];
	toRet[1] = 0;
	Chessman* temp;
	int srcLetter = 0;
	int srcNum = 0;
	int dstLetter = 0;
	int dstNum = 0;

	convertPlace((string)src, srcNum, srcLetter);
	convertPlace((string)dst, dstNum, dstLetter);

	if (srcNum < 0 || srcNum > BOARD_SIZE || srcLetter < 0 || srcLetter > BOARD_SIZE || dstLetter < 0 || dstLetter > BOARD_SIZE || dstNum < 0 || dstNum > BOARD_SIZE)
	{
		toRet[0] = INVALID_PLACE_INDEX;
	}
	else if (isBlack(hasChessman(src)) != convertTurnToChar(_turn)) //check if in the sorce place there is a valid chessman
	{
		toRet[0] = SOURCE_PLACE_INVALID;
	}
	else
	{
		toRet[0] = _board[srcNum][srcLetter]->validMove(movement, *this)[0];

		if (toRet[0] == VALID_MOVEMENT)
		{
			//save dst
			temp = _board[dstNum][dstLetter];
			//change places
			_board[dstNum][dstLetter] = _board[srcNum][srcLetter];
			_board[srcNum][srcLetter] = NULL;

			//check if there is shah on himself
			if (isShah(convertTurnToChar(_turn)))
			{
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

			_board[srcNum][srcLetter] = _board[dstNum][dstLetter];
			_board[dstNum][dstLetter] = temp;
		}
	}

	if (toRet[0] == VALID_MOVEMENT || toRet[0] == SHAH_ON_OPPONENT)
	{
		changePlace(movement);
		chTurn();
	}

	return toRet;
}

char Game::hasChessman(string place)
{
	char toRet = NULL;
	int i = 0;
	int j = 0;
	convertPlace(place, i, j);
	if (_board[i][j] != NULL)
	{
		toRet = _board[i][j]->getType();
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
	int srcLetter = 0;
	int srcNum = 0;
	int dstLetter = 0;
	int dstNum = 0;

	convertPlace(movement.substr(0,2) ,srcNum, srcLetter);
	convertPlace(movement.substr(2, 2), dstNum, dstLetter);
	
	Chessman* temp = _board[srcNum][srcLetter]; //save the chessman to move
	_board[srcNum][srcLetter] = NULL; //empy the sorce place
	if (_board[dstNum][dstLetter]) //eat the chessman in destination place if there is, Yummi!!
	{
		delete _board[dstNum][dstLetter];
	}
	_board[dstNum][dstLetter] = temp; //save in destination place the chessman

	_board[dstNum][dstLetter]->setPlace(movement.substr(2, 2));
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

void Game::chTurn()
{
	if (_turn == BLACK_NUM)
	{
		_turn = WHITE_NUM;
	}
	else
	{
		_turn = BLACK_NUM;
	}
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
	j = place[0] - VALUE_a;
	i = BOARD_SIZE - (place[1] - VALUE_1) - 1;
}

string Game::getKingPlace(char player)
{
	string place = "";

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (_board[i][j] == NULL)
			{
				continue;
			}
			else if ((player == WHITE_CH && _board[i][j]->getType() == KING_W) ||
				     (player == BLACK_CH && _board[i][j]->getType() == KING_B))
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
	int j = 0;
	int i = 0;
	bool isShah = false;
	convertPlace(kingPlace, i, j);

	for (i = i+1; i < BOARD_SIZE; i++)
	{
		if (_board[i][j])
		{
			if ((_board[i][j]->getType() == ROOK_W && player == BLACK_CH) ||
				(_board[i][j]->getType() == ROOK_B && player == WHITE_CH))
			{
				isShah = true;
			}
			break;
		}
	}

	for (i = i - 1; i >= 0; i--)
	{
		if (_board[i][j])
		{
			if ((_board[i][j]->getType() == ROOK_W && player == BLACK_CH) ||
				(_board[i][j]->getType() == ROOK_B && player == WHITE_CH))
			{
				isShah = true;
			}
			break;
		}
	}

	convertPlace(kingPlace, i, j);

	for (j = j + 1; j < BOARD_SIZE; j++)
	{
		if (_board[i][j])
		{
			if ((_board[i][j]->getType() == ROOK_W && player == BLACK_CH) ||
				(_board[i][j]->getType() == ROOK_B && player == WHITE_CH))
			{
				isShah = true;
			}
			break;
		}
	}

	for (j = j - 1; j >= 0; j--)
	{
		if (_board[i][j])
		{
			if ((_board[i][j]->getType() == ROOK_W && player == BLACK_CH) || (_board[i][j]->getType() == ROOK_B && player == WHITE_CH))
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
	int j = 0;
	int i = 0;
	bool isShah = false;

	convertPlace(kingPlace, i, j);

	if (i > 0)
	{
		isShah = ((player == BLACK_CH && hasChessman(convertPlace(i - 1, j)) == KING_B) || (player == WHITE_CH && hasChessman(convertPlace(i - 1, j)) == KING_W));
	}
	if (j > 0 && !isShah)
	{
		isShah = ((player == BLACK_CH && hasChessman(convertPlace(i, j - 1)) == KING_B) || (player == WHITE_CH && hasChessman(convertPlace(i, j - 1)) == KING_W));
	}
	if (j < BOARD_SIZE-1 && !isShah)
	{
		isShah = ((player == BLACK_CH && hasChessman(convertPlace(i, j + 1)) == KING_B) || (player == WHITE_CH && hasChessman(convertPlace(i, j + 1)) == KING_W));
	}
	if (i < BOARD_SIZE-1 && !isShah)
	{
		isShah = ((player == BLACK_CH && hasChessman(convertPlace(i + 1, j)) == KING_B) || (player == WHITE_CH && hasChessman(convertPlace(i + 1, j)) == KING_W));
	}
	if (j > 0 && i > 0 && !isShah)
	{
		isShah = ((player == BLACK_CH && hasChessman(convertPlace(i - 1, j - 1)) == KING_B) || (player == WHITE_CH && hasChessman(convertPlace(i - 1, j - 1)) == KING_W));
	}
	if (j > 0 && i < BOARD_SIZE-1 && !isShah)
	{
		isShah = ((player == BLACK_CH && hasChessman(convertPlace(i + 1, j - 1)) == KING_B) || (player == WHITE_CH && hasChessman(convertPlace(i + 1, j - 1)) == KING_W));
	}
	if (i > 0 && j < BOARD_SIZE-1 && !isShah)
	{
		isShah = ((player == BLACK_CH && hasChessman(convertPlace(i - 1, j + 1)) == KING_B) || (player == WHITE_CH && hasChessman(convertPlace(i - 1, j + 1)) == KING_W));
	}
	if (j < BOARD_SIZE-1 && i < BOARD_SIZE-1 && !isShah)
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

char Game::convertTurnToChar(char player)
{
	char ret = 0;
	if (player == WHITE_NUM)
	{
		ret = WHITE_CH;
	}
	else
	{
		ret = BLACK_CH;
	}

	return ret;
}