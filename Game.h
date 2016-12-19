#ifndef GAME_H
#define GAME_H

#include <iostream> // input-output library
#include <string> // string library
#include "Chessman.h"

using namespace std; // using std functions

#define BOARD_SIZE 8
#define VALUE_1 49
#define VALUE_a 97
#define QUEEN_B 'q'
#define KING_B 'k'
#define BISHOP_B 'b'
#define KNIGHT_B 'n'
#define ROOK_B 'r'
#define PAWN_B 'p'
#define QUEEN_W 'Q'
#define KING_W 'K'
#define BISHOP_W 'B'
#define KNIGHT_W 'N'
#define ROOK_W 'R'
#define PAWN_W 'P'
#define BLACK 'b'
#define WITE 'w'

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
	string getKingPlace(char player);

	bool shahRook(string kingPlace, char player);
	bool shahKing(string kingPlace, char player);

public:
	Game(char turn, string board);
	~Game();

	string move(string movement);
	char hasChessman(string place);
	string turn(string movement);
	void printBoard();
};

#endif