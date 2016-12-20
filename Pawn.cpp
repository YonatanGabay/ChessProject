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

char* Pawn::validMove(string movement, Game game)
{
	//0
	//1
	//2
	//4
	//5
	const int LETTER = 0, NUM = 1;
	const int TO1 = 2, TO2 = 4, FROM1 = 0, FROM2 = 2;

	const string to = movement.substr(TO1, TO2);
	const string from = movement.substr(FROM1, FROM2);

	char ret[RET_SIZE] = { 0 };
	const char letterTo = to[LETTER], numTo = to[NUM];
	const char letterFrom = from[LETTER], numFrom = from[NUM];

	if (this->getPlace() == from)
	{
		if (to != from)
		{
			if (game.isBlack(game.hasChessman(from)) != game.isBlack(game.hasChessman(to))) // if is not same color
			{
				if (letterFrom == letterTo)
				{
					// TO DO
				}
				else if (letterFrom == letterTo + 1 || letterFrom == letterTo - 1)
				{
					if (this->getType() == PAWN_W)
					{
						if (numFrom == numTo + 1)
						{
							if (game.isBlack(game.hasChessman(to)) == BLACK)
							{
								//valid
							}
							else
							{
								ret[0] = INVALID_MOVEMENT; // error - invalid movement
							}
						}
						else
						{
							ret[0] = INVALID_MOVEMENT; // error - invalid movement
						}
					}
					else // if (this->getType() == PAWN_B)
					{
						if (numFrom == numTo - 1)
						{
							if (game.isBlack(game.hasChessman(to)) == WHITE)
							{
								//valid
							}
							else
							{
								ret[0] = INVALID_MOVEMENT; // error - invalid movement
							}
						}
						else
						{
							ret[0] = INVALID_MOVEMENT; // error - invalid movement
						}
					}
				}
				else
				{
					ret[0] = INVALID_MOVEMENT; // error - invalid movement
				}
			}

			else // if there same color
			{
				ret[0] = DEST_PLACE_INVALID; // error - try to eat chessman with same color
			}
		}
		else // if (to == from)
		{
			ret[0] = SAME_SOURCE_AND_DEST;
		}
	}
	else
	{
		cout << "ERROR this place Pawn!!!" << endl;
	}

	return ret;
}

