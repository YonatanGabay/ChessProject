#ifndef CHESSMAN_H
#define CHESSMAN_H

#include <iostream> // input-output library
#include <string> // string library

using namespace std; // using std functions


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

	virtual char validMove(string move) = 0;
};

#endif