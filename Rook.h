#ifndef ROOK_H
#define ROOK_H

#include <iostream> // input-output library
#include <string> // string library
#include "Chessman.h"

using namespace std; // using std functions


class Rook : Chessman
{
private:

public:
	Rook(char type, string place);
	~Rook();

	virtual char validMove(string newPlace);
};

#endif