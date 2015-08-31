
#include "terminaldisplay.h"

using namespace zeno;

#include <iostream>

TerminalDisplay::TerminalDisplay() {

}

TerminalDisplay::~TerminalDisplay() {

}

// ASCII board style taken from GNUBG
// but the code is completely my own
// 
//                  Position ID: 0123456789ABCD 
//                  Match ID   : 0123456789ABCD
//  +13-14-15-16-17-18------19-20-21-22-23-24-+     O: gnubg (Cube: 2)
//  |                  |   | O  O  O  O     O | OO  0 points
//  |                  |   | O     O          | OO  Cube offered at 2
//  |                  |   |       O          | O
//  |                  |   |                  | O
//  |                  |   |                  | O   
// v|                  | Z |                  |     Cube: 1 (7 point match)
//  |                  |   |                  | X    
//  |                  |   |                  | X
//  |                  |   |                  | X
//  |                  |   |       X  X  X  X | X   Rolled 11
//  |                  |   |    X  X  X  X  X | XX  0 points
//  +12-11-10--9--8--7-------6--5--4--3--2--1-+     X: Gary (Cube: 2)
// 
// 

void checkerDisplay(
	const Board & board,
	int yCur,
	int xCur,
	int yMax,
	bool posPlayerOnBottom,
	const std::vector<char> &extraCheckers,
	std::ostream &outStream
	) {

	outStream << " ";

	int posx;
	int negx;
	if (posPlayerOnBottom) {
		posx = xCur-1;
		negx = (25-xCur)-1;
	} else {
		posx = (25-xCur)-1;
		negx = xCur-1;
	}

	if (board.getPosPlayerCheckers(posx) >= yCur) {
		if (yCur == yMax && board.getPosPlayerCheckers(posx) > yMax) {
			outStream << extraCheckers[board.getPosPlayerCheckers(posx)];
		} else {
			outStream << "X";
		}
	} else if (board.getNegPlayerCheckers(negx) >= yCur) {
		if (yCur == yMax && board.getNegPlayerCheckers(negx) > yMax) {
			outStream << extraCheckers[board.getNegPlayerCheckers(negx)];
		} else {
			outStream << "O";
		}
	} else {
		outStream << " ";
	}

	outStream << " ";
}

void TerminalDisplay::showBoard(const GameState & gameState, std::ostream &outStream) {

	Board board = gameState.getBoard();
	bool posPlayerOnBottom = gameState.isPositivePlayerOnTurn();

	char leftSideCharacter = '|';
	char rightSideCharacter = '|';
	std::vector<char> extraCheckers = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

	outStream << " +13-14-15-16-17-18------19-20-21-22-23-24-+ ";
	outStream << std::endl;

	int ymin = 1;
	int ymax = 5;
	for (int ytop=ymin;ytop<=ymax;ytop++) {
		outStream << " ";
		outStream << leftSideCharacter;

		for (int x=13;x<=18;x++) {
			checkerDisplay(board,ytop,x,ymax,posPlayerOnBottom,extraCheckers,outStream);
		}

		// eventually checkers on the bar will go here
		outStream << rightSideCharacter << "   " << leftSideCharacter;

		for (int x=19;x<=24;x++) {
			checkerDisplay(board,ytop,x,ymax,posPlayerOnBottom,extraCheckers,outStream);
		}

		outStream << rightSideCharacter;
		outStream << " ";
		outStream << std::endl;
	}

	outStream << " ";
	outStream << rightSideCharacter;
	outStream << "                  ";
	outStream << leftSideCharacter;
	outStream << " Z ";
	outStream << leftSideCharacter;
	outStream << "                  ";
	outStream << rightSideCharacter;
	outStream << std::endl;

	for (int ybottom=ymax;ybottom>=ymin;ybottom--) {
		outStream << " ";
		outStream << leftSideCharacter;

		for (int x=12;x>=7;x--) {
			checkerDisplay(board,ybottom,x,ymax,posPlayerOnBottom,extraCheckers,outStream);
		}

		// eventually checkers on the bar will go here
		outStream << "|   |";

		for (int x=6;x>=1;x--) {
			checkerDisplay(board,ybottom,x,ymax,posPlayerOnBottom,extraCheckers,outStream);
		}

		outStream << rightSideCharacter;
		outStream << " ";
		outStream << std::endl;
	}


	outStream << " +12-11-10--9--8--7-------6--5--4--3--2--1-+ ";
	outStream << std::endl;

}