#include <iostream> // input-output library
#include <string> // string library
#include "Chessman.h"

using namespace std; // using std functions

Chessman::Chessman(char type, string place) : _place(place)
{
	this->_type;
}

Chessman::~Chessman()
{

}

char Chessman::getType()
{
	return this->_type;
}

string Chessman::getPlace()
{
	return this->_place;
}

void Chessman::setPlace(string place)
{
	this->_place = place;
}
