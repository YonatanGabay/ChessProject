#ifndef KNIGHT_H
#define KNIGHT_H

#include <iostream> // input-output library
#include <string> // string library
#include "Chessman.h"

using namespace std; // using std functions


class Knight : Chessman
{
private:

public:
	Knight(char type, string place);
	~Knight();

	virtual char validMove(string newPlace);
};

#endif