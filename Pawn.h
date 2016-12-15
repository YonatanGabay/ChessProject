#ifndef PAWN_H
#define PAWN_H

#include <iostream> // input-output library
#include <string> // string library
#include "Chessman.h"

using namespace std; // using std functions


class Pawn : Chessman
{
private:

public:
	Pawn(char type, string place);
	~Pawn();

	virtual char validMove(string newPlace);
};

#endif