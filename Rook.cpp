#include <iostream> // input-output library
#include <string> // string library
#include "Chessman.h"
#include "Rook.h"

Rook::Rook(char type, string place) : Chessman(type, place)
{

}

Rook::~Rook()
{

}

string Rook::validMove(string movement, Game game)
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
			if (LETTER_TO == LETTER_FROM) // if it same letter
			{
				bool valid = true;
				char from_[] = { LETTER_FROM ,  NUM_FROM };

				if (NUM_TO > NUM_FROM)
					for (from_[NUM_INDEX] += 1; from_[NUM_INDEX] < NUM_TO; from_[NUM_INDEX]++)
						if (game.hasChessman(string(from_)) != NULL)
							valid = false;

				if (NUM_TO < NUM_FROM)
					for (from_[NUM_INDEX] -= 1; from_[NUM_INDEX] > NUM_TO; from_[NUM_INDEX]--)
						if (game.hasChessman(string(from_)) != NULL)
							valid = false;

				if (valid)
					ret[RET_INDEX] = VALID_MOVEMENT;

				else // if (!valid)
					ret[RET_INDEX] = INVALID_MOVEMENT;

			}
			else if (NUM_TO == NUM_FROM) // if is same number
			{
				bool valid = true;
				char from_[] = { LETTER_FROM ,  NUM_FROM };

				if (LETTER_TO > LETTER_FROM)
					for (from_[LETTER_INDEX] += 1; from_[LETTER_INDEX] < LETTER_TO; from_[LETTER_INDEX]++)
						if (game.hasChessman(string(from_)) != NULL)
							valid = false;

				if (LETTER_TO < LETTER_FROM)
					for (from_[LETTER_INDEX] -= 1; from_[LETTER_INDEX] > LETTER_TO; from_[LETTER_INDEX]--)
						if (game.hasChessman(string(from_)) != NULL)
							valid = false;

				if (valid)
					ret[RET_INDEX] = VALID_MOVEMENT;

				else // if (!valid)
					ret[RET_INDEX] = INVALID_MOVEMENT;

			}
			else // if it not same letter and number
			{
				ret[RET_INDEX] = INVALID_MOVEMENT;
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
