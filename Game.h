#ifndef GAME_H
#define GAME_H

#include <iostream> // input-output library
#include <string> // string library
#include "Chessman.h"

using namespace std; // using std functions

#define BOARD_SIZE 8

class Game
{
private:
	char turn;
	Chessman* board[BOARD_SIZE][BOARD_SIZE];

	char win();
	bool isShah(char player);
	bool isFreePath(string movement);
	void changePlace(string movement);

public:
	Game();
	~Game();

	string move(string movement);
	bool hasChessman(string place);
};

#endif