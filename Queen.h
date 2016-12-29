#ifndef QUEEN_H
#define QUEEN_H

#include <iostream> // input-output library
#include <string> // string library
#include "Chessman.h"

using namespace std; // using std functions


class Queen : public Chessman
{
private:

public:
	Queen(char type, string place);
	~Queen();

	virtual string validMove(string movement, Game game);
};

#endif