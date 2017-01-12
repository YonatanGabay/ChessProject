#include <iostream> // input-output library
#include <string> // string library
#include "Chessman.h"
#include "Knight.h"

Knight::Knight(char type, string place) : Chessman(type, place)
{

}

Knight::~Knight()
{

}

string Knight::validMove(string movement, Game game)
{
	const int LETTER = 0, NUM = 1;
	const int TO1 = 2, TO2 = 4, FROM1 = 0, FROM2 = 2;

	const string TO = movement.substr(TO1, TO2);
	const string FROM = movement.substr(FROM1, FROM2);

	string ret = "*";
	ret[0] = INVALID_MOVEMENT;
	const char LETTER_TO = TO[LETTER], NUM_TO = TO[NUM];
	const char LETTER_FROM = FROM[LETTER], NUM_FROM = FROM[NUM];

	if (TO == FROM)
	{
		ret[0] = SAME_SOURCE_AND_DEST;
	}
	else if ((LETTER_TO == LETTER_FROM + 2) && ((NUM_TO == NUM_FROM + 1) || (NUM_TO == NUM_FROM - 1)))
	{
		ret[0] = VALID_MOVEMENT;
	}
	else if ((LETTER_TO == LETTER_FROM - 2) && ((NUM_TO == NUM_FROM + 1) || (NUM_TO == NUM_FROM - 1)))
	{
		ret[0] = VALID_MOVEMENT;
	}
	else if ((NUM_TO == NUM_FROM + 2) && ((LETTER_TO == LETTER_FROM + 1) || (LETTER_TO == LETTER_FROM - 1)))
	{
		ret[0] = VALID_MOVEMENT;
	}
	else if ((NUM_TO == NUM_FROM - 2) && ((LETTER_TO == LETTER_FROM + 1) || (LETTER_TO == LETTER_FROM - 1)))
	{
		ret[0] = VALID_MOVEMENT;
	}

	if ((ret[0] == VALID_MOVEMENT) && (game.isBlack(game.hasChessman(TO)) == game.getTurn()))
	{
		ret[0] = DEST_PLACE_INVALID;
	}

	return ret;
}
