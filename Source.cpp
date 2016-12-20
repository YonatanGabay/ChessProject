#include "Pipe.h"
#include <iostream>
#include <thread>
#include <cstdlib>
#include <string>
#include "Game.h"
using namespace std;

#define TURN 64

void main()
{
	const int ADD_TO_ASCII = 48;

	srand(time(NULL));

	Pipe p;
	bool isConnect = p.connect();
	
	string ans;
	while (!isConnect)
	{
		cout << "cant connect to graphics" << endl;
		cout << "Do you try to connect again or exit? (0-try again, 1-exit)" << endl;
		cin >> ans;

		if (ans == "0")
		{
			cout << "trying connect again.." << endl;
			Sleep(5000);
			isConnect = p.connect();
		}
		else 
		{
			p.close();
			return;
		}
	}
	

	char msgToGraphics[1024];
	// msgToGraphics should contain the board string accord the protocol
	// YOUR CODE

	// get rand player
	int turn = rand() % 2;
	turn += ADD_TO_ASCII;

	// make start str and put the first layer
	strcpy_s(msgToGraphics, "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr*");
	msgToGraphics[TURN] = (char)turn;

	Game game((char)turn, string(msgToGraphics));

	game.printBoard();

	p.sendMessageToGraphics(msgToGraphics);   // send the board string

	// get message from graphics
	string msgFromGraphics = p.getMessageFromGraphics();

	while (msgFromGraphics != "quit")
	{
		// should handle the string the sent from graphics
		// according the protocol. Ex: e2e4           (move e2 to e4)
		
		// YOUR CODE

		const char* data = game.move(msgFromGraphics).data();
		cout << data << endl;
		strcpy_s(msgToGraphics, data); // msgToGraphics should contain the result of the operation

		/******* JUST FOR EREZ DEBUGGING ******
		int r = rand() % 10; // just for debugging......
		msgToGraphics[0] = (char)(1 + '0');
		msgToGraphics[1] = 0;
		/******* JUST FOR EREZ DEBUGGING ******/


		// return result to graphics		
		p.sendMessageToGraphics(msgToGraphics);   

		// get message from graphics
		msgFromGraphics = p.getMessageFromGraphics();
	}

	p.close();
}
