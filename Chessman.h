#ifndef CHESSMAN_H
#define CHESSMAN_H

#include <iostream> // input-output library
#include <string> // string library
#include "Game.h"

using namespace std; // using std functions

class Game;

class Chessman
{
private:
	char _type;
	string _place;

public:
	Chessman(char type, string place);
	~Chessman();

	char getType();
	string getPlace();
	void setPlace(string place);

	virtual string validMove(string movement, Game game) = 0;
};

#endif