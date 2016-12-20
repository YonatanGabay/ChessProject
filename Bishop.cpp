#include <iostream> // input-output library
#include <string> // string library
#include "Chessman.h"
#include "Bishop.h"
#include "Game.h"

Bishop::Bishop(char type, string place) : Chessman(type, place)
{

}

Bishop::~Bishop()
{

}

char* Bishop::validMove(string newPlace, Game game)
{
	// need to do
	return NULL;
}
