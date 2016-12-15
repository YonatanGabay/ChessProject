#ifndef BISHOP_H
#define BISHOP_H

#include <iostream> // input-output library
#include <string> // string library
#include "Chessman.h"

using namespace std; // using std functions


class Bishop : public Chessman
{
private:

public:
	Bishop(char type, string place);
	~Bishop();

	virtual char validMove(string newPlace);
};

#endif