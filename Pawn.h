#ifndef PAWN_H
#define PAWN_H

#include <iostream> // input-output library
#include <string> // string library
#include "Chessman.h"
#include "Game.h"

using namespace std; // using std functions

#define	RET_SIZE 2


class Pawn : public Chessman
{
private:

public:
	Pawn(char type, string place);
	~Pawn();

	virtual char* validMove(string movement, Game game);
};

#endif