#include <iostream> // input-output library
#include <string> // string library
#include "Chessman.h"
#include "Pawn.h"
#include "Game.h"

Pawn::Pawn(char type, string place) : Chessman(type, place)
{

}

Pawn::~Pawn()
{

}

string Pawn::validMove(string movement, Game game)
{
	const int RET_INDEX = 0;
	const int LETTER = 0, NUM = 1;
	const int TO1 = 2, TO2 = 4, FROM1 = 0, FROM2 = 2;

	const string TO = movement.substr(TO1, TO2);
	const string FROM = movement.substr(FROM1, FROM2);

	string ret = "*";
	const char LETTER_TO = TO[LETTER], NUM_TO = TO[NUM];
	const char LETTER_FROM = FROM[LETTER], NUM_FROM = FROM[NUM];

	char cheekMove[] = { LETTER_TO, "*" };

	if (TO != FROM) // if src and dst different
	{
		if (game.isBlack(game.hasChessman(FROM)) != game.isBlack(game.hasChessman(TO))) // if is not same color
		{
			if (LETTER_FROM == LETTER_TO)
			{
				if (this->getType() == PAWN_W)
				{
					cheekMove[1] = NUM_TO + 1;

					if (NUM_TO + 1 == NUM_FROM && game.hasChessman(TO) == NULL)
						ret[RET_INDEX] = VALID_MOVEMENT;

					else if (NUM_TO + 2 == NUM_FROM && game.hasChessman(TO) == NULL)
						if (NUM_FROM == WHITE_START_NUM && game.hasChessman(string(cheekMove)) == NULL)
							ret[RET_INDEX] = VALID_MOVEMENT;

						else
							ret[RET_INDEX] = INVALID_MOVEMENT;
				}
				else // if (this->getType() == PAWN_B)
				{
					cheekMove[1] = NUM_TO - 1;

					if (NUM_TO - 1 == NUM_FROM && game.hasChessman(TO) == NULL)
						ret[RET_INDEX] = VALID_MOVEMENT;

					else if (NUM_TO - 2 == NUM_FROM && game.hasChessman(TO) == NULL)
						if (NUM_FROM == BLACK_START_NUM && game.hasChessman(string(cheekMove)) == NULL)
							ret[RET_INDEX] = VALID_MOVEMENT;

					else
						ret[RET_INDEX] = INVALID_MOVEMENT;
				}
			}
			else if (LETTER_FROM == LETTER_TO + 1 || LETTER_FROM == LETTER_TO - 1)
			{
				if (this->getType() == PAWN_W)
				{
					if (NUM_FROM == NUM_TO + 1)
					{
						if (game.isBlack(game.hasChessman(TO)) == BLACK_CH)
						{
							ret[RET_INDEX] = VALID_MOVEMENT;
						}
						else
						{
							ret[RET_INDEX] = INVALID_MOVEMENT; // error - invalid movement
						}
					}
					else
					{
						ret[RET_INDEX] = INVALID_MOVEMENT; // error - invalid movement
					}
				}
				else // if (this->getType() == PAWN_B)
				{
					if (NUM_FROM == NUM_TO - 1)
					{
						if (game.isBlack(game.hasChessman(TO)) == WHITE_CH)
						{
							ret[RET_INDEX] = VALID_MOVEMENT;
						}
						else
						{
							ret[RET_INDEX] = INVALID_MOVEMENT; // error - invalid movement
						}
					}
					else
					{
						ret[RET_INDEX] = INVALID_MOVEMENT; // error - invalid movement
					}
				}
			}
			else
			{
				ret[RET_INDEX] = INVALID_MOVEMENT; // error - invalid movement
			}
		}

		else // if there same color
		{
			ret[RET_INDEX] = DEST_PLACE_INVALID; // error - try to eat chessman with same color
		}
	}
	else // if (TO == FROM)
	{
		ret[RET_INDEX] = SAME_SOURCE_AND_DEST;
	}

	return ret;
}

