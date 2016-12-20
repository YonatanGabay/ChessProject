#ifndef GAME_H
#define GAME_H

#include <iostream> // input-output library
#include <string> // string library
#include "Chessman.h"

using namespace std; // using std functions

#define BOARD_SIZE 8

#define VALUE_1 49
#define VALUE_a 97

#define BLACK_CH 'b'
#define WHITE_CH 'w'
#define BLACK_NUM '1'
#define WHITE_NUM '0'

#define QUEEN_B 'q'
#define QUEEN_W 'Q'
#define KING_B 'k'
#define KING_W 'K'
#define BISHOP_B 'b'
#define BISHOP_W 'B'
#define KNIGHT_B 'n'
#define KNIGHT_W 'N'
#define ROOK_B 'r'
#define ROOK_W 'R'
#define PAWN_B 'p'
#define PAWN_W 'P'

// responses to fronted
#define VALID_MOVE '0'
#define SHAH_ON_OPPONENT '1'
#define SOURCE_PLACE_INVALID '2'
#define DEST_PLACE_INVALID '3'
#define SHAH_ON_HIMSELF '4'
#define INVALID_PLACE_INDEX '5'
#define INVALID_MOVEMENT '6'
#define SAME_SOURCE_AND_DEST '7'

#define LETTERS_CHECKER 60

class Chessman;

class Game
{
private:
	char _turn;
	Chessman* _board[BOARD_SIZE][BOARD_SIZE];

	char win();

	bool isShah(char player);
	bool isFreePath(string movement);

	string getKingPlace(char player);
	void changePlace(string movement);
	
	static string convertPlace(int i, int j);
	static Chessman* makeChessman(char type, string place);
	

	bool shahRook(string kingPlace, char player);
	bool shahKing(string kingPlace, char player);
	bool shahPawn(string kingPlace);
	bool shahBishop(string kingPlace);
	bool shahKnight(string kingPlace);
	bool shahQueen(string kingPlace);

public:
	Game(const Game& other);
	Game(char turn, string board);
	~Game();

	string turn(string movement);
	string move(string movement);

	int isBlack(char chessman);
	char hasChessman(string place);

	void printBoard();
};

#endif