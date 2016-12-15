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
	char _turn;
	Chessman* _board[BOARD_SIZE][BOARD_SIZE];

	char win();
	bool isShah(char player);
	bool isFreePath(string movement);
	void changePlace(string movement);
	static Chessman* makeCessman(char type, string place);
	static string convertPlace(int i, int j);

public:
	Game(char turn, string board);
	~Game();

	string move(string movement);
	bool hasChessman(string place);
	string turn(string movement);
	void printBoard();
};

#endif