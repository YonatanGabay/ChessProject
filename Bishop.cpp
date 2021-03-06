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

string Bishop::validMove(string movement, Game game)
{
	const int RET_INDEX = 0;
	const int LETTER_INDEX = 0, NUM_INDEX = 1;
	const int TO1 = 2, TO2 = 4, FROM1 = 0, FROM2 = 2;

	const string TO = movement.substr(TO1, TO2);
	const string FROM = movement.substr(FROM1, FROM2);

	string ret = "*";
	const char LETTER_TO = TO[LETTER_INDEX], NUM_TO = TO[NUM_INDEX];
	const char LETTER_FROM = FROM[LETTER_INDEX], NUM_FROM = FROM[NUM_INDEX];

	if (TO != FROM) // if is valid dest
	{
		if (game.isBlack(game.hasChessman(FROM)) != game.isBlack(game.hasChessman(TO))) // if is not same color
		{
			if (LETTER_TO - NUM_TO == LETTER_FROM - NUM_FROM) // if is same remainder - option one
			{
				bool valid = true;
				char from_[] = { LETTER_FROM, NUM_FROM }; // make copy to source place

				if (LETTER_TO > LETTER_FROM)
				{
					for (int i = (int)LETTER_FROM + 1; i < (int)LETTER_TO; i++)
					{
						from_[LETTER_INDEX]++;
						from_[NUM_INDEX]++;

						if (game.hasChessman(string(from_)) != NULL) // cheek the way
							valid = false;
					}

					if (valid)
						ret[RET_INDEX] = VALID_MOVEMENT;

					else // if (!valid)
						ret[RET_INDEX] = INVALID_MOVEMENT;
				}
				else // if (LETTER_TO < LETTER_FROM)
				{

					for (int i = (int)LETTER_FROM - 1; i != (int)LETTER_TO; i--)
					{
						from_[LETTER_INDEX]--;
						from_[NUM_INDEX]--;

						if (game.hasChessman(string(from_)) != NULL) // cheek the way
							valid = false;
					}

					if (valid)
						ret[RET_INDEX] = VALID_MOVEMENT;

					else // if (!valid)
						ret[RET_INDEX] = INVALID_MOVEMENT;
				}
			}
			else // if is not same remainder
			{
				bool valid = true;
				bool found = false;
				char from_[] = { LETTER_FROM, NUM_FROM };

				if (LETTER_TO > LETTER_FROM)
				{
					for (int i = (int)LETTER_FROM + 1; i < (int)LETTER_TO; i++)
					{
						from_[LETTER_INDEX]++;
						from_[NUM_INDEX]--;

						if (game.hasChessman(string(from_)) != NULL) // cheek the way
							valid = false;
					}

					if (valid)
						ret[RET_INDEX] = VALID_MOVEMENT;

					else // if (!valid)
						ret[RET_INDEX] = INVALID_MOVEMENT;
				}
				else // if (LETTER_TO < LETTER_FROM)
				{
					for (int i = (int)LETTER_TO - 1; i > (int)LETTER_FROM; i--)
					{
						from_[LETTER_INDEX]--;
						from_[NUM_INDEX]++;
						if (game.hasChessman(string(from_)) != NULL) // cheek the way
							valid = false;
					}

					if (valid)
						ret[RET_INDEX] = VALID_MOVEMENT;

					else // if (!valid)
						ret[RET_INDEX] = INVALID_MOVEMENT;
				}
			}
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
