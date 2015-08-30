
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
void TerminalDisplay::showBoard(const GameState & gameState, std::ostream &outStream) {

	Board board = gameState.getBoard();
	bool posPlayerOnBottom = gameState.isPositivePlayerOnTurn();

	char leftSideCharacter = '|';
	char rightSideCharacter = '|';
	char extraCheckers[16] = "123456789ABCDEF";

	outStream << " +13-14-15-16-17-18------19-20-21-22-23-24-+ ";
	outStream << std::endl;

	int ymin = 1;
	int ymax = 5;
	for (int ytop=ymin;ytop<=ymax;ytop++) {
		outStream << " ";
		outStream << leftSideCharacter;

		for (int x=13;x<=18;x++) {
			outStream << " ";

			int posx;
			int negx;
			if (posPlayerOnBottom) {
				posx = x-1;
				negx = 24-x;
			} else {
				posx = 24-x;
				negx = x-1;
			}

			if (board.getPosPlayerCheckers(posx) >= ytop) {
				if (ytop == ymax && board.getPosPlayerCheckers(posx) > ymax) {
					outStream << extraCheckers[board.getPosPlayerCheckers(posx)];
				} else {
					outStream << "X";
				}
			} else if (board.getNegPlayerCheckers(negx) >= ytop) {
				if (ytop == ymax && board.getNegPlayerCheckers(negx) > ymax) {
					outStream << extraCheckers[board.getNegPlayerCheckers(negx)];
				} else {
					outStream << "O";
				}
			} else {
				outStream << " ";
			}

			outStream << " ";
		}

		// eventually checkers on the bar will go here
		outStream << rightSideCharacter << "   " << leftSideCharacter;

		for (int x=19;x<=24;x++) {
			outStream << " ";

			int posx;
			int negx;
			if (posPlayerOnBottom) {
				posx = x-1;
				negx = 24-x;
			} else {
				posx = 24-x;
				negx = x-1;
			}

			if (board.getPosPlayerCheckers(posx) >= ytop) {
				outStream << "X";
			} else if (board.getNegPlayerCheckers(negx) >= ytop) {
				outStream << "O";
			} else {
				outStream << " ";
			}

			outStream << " ";
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

	for (int ybottom=5;ybottom>=1;ybottom--) {
		outStream << " ";
		outStream << leftSideCharacter;

		for (int x=12;x>=7;x--) {
			outStream << " ";

			int posx;
			int negx;
			if (posPlayerOnBottom) {
				posx = x-1;
				negx = 24-x;
			} else {
				posx = 24-x;
				negx = x-1;
			}

			if (board.getPosPlayerCheckers(posx) >= ybottom) {
				outStream << "X";
			} else if (board.getNegPlayerCheckers(negx) >= ybottom) {
				outStream << "O";
			} else {
				outStream << " ";
			}

			outStream << " ";
		}

		// eventually checkers on the bar will go here
		outStream << "|   |";

		for (int x=6;x>=1;x--) {
			outStream << " ";

			int posx;
			int negx;
			if (posPlayerOnBottom) {
				posx = x-1;
				negx = 24-x;
			} else {
				posx = 24-x;
				negx = x-1;
			}

			if (board.getPosPlayerCheckers(posx) >= ybottom) {
				outStream << "X";
			} else if (board.getNegPlayerCheckers(negx) >= ybottom) {
				outStream << "O";
			} else {
				outStream << " ";
			}

			outStream << " ";
		}

		outStream << rightSideCharacter;
		outStream << " ";
		outStream << std::endl;
	}


	outStream << " +12-11-10--9--8--7-------6--5--4--3--2--1-+ ";
	outStream << std::endl;

}