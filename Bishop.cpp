#include <iostream> // input-output library
#include <string> // string library
#include "Chessman.h"
#include "Bishop.h"
#include "Game.h"

Bishop::Bishop(char type, string place) : Chessman(type, place)
{

}

Bishop::~Bishop()
{

}

char* Bishop::validMove(string movement, Game game)
{
	/*
	VALID_MOVEMENT '0' - מהלך חוקי
	INVALID_MOVEMENT '6' - תנועה לא חוקית של הכלי
	*/
	const int RET_INDEX = 0;
	const int LETTER = 0, NUM = 1;
	const int TO1 = 2, TO2 = 4, FROM1 = 0, FROM2 = 2;

	const string TO = movement.substr(TO1, TO2);
	const string FROM = movement.substr(FROM1, FROM2);

	char ret[RET_SIZE] = { NULL };
	const char LETTER_TO = TO[LETTER], NUM_TO = TO[NUM];
	const char LETTER_FROM = FROM[LETTER], NUM_FROM = FROM[NUM];

	if (TO != FROM)
	{
		if (game.isBlack(game.hasChessman(FROM)) != game.isBlack(game.hasChessman(TO))) // if is not same color
		{

		}

		else // if source and dest is same color
		{
			ret[RET_INDEX] = DEST_PLACE_INVALID;
		}
	}

	else // if (TO == FROM)
	{
		ret[RET_INDEX] = SAME_SOURCE_AND_DEST;
	}


	return ret;
}
