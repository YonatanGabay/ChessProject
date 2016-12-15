#ifndef KING_H
#define KING_H

#include <iostream> // input-output library
#include <string> // string library
#include "Chessman.h"

using namespace std; // using std functions


class King : Chessman
{
private:

public:
	King();
	~King();

	virtual char validMove(string newPlace);
};

#endif