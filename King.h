#ifndef KING_H
#define KING_H

#include <iostream> // input-output library
#include <string> // string library
#include "Chessman.h"

using namespace std; // using std functions


class King : public Chessman
{
private:

public:
	King(char type, string place);
	~King();

	virtual char* validMove(string movement, Game game);
};

#endif