
#include "terminaldisplay.h"

using namespace zeno;

#include <iostream>
#include <string>

const std::string TerminalDisplay::m_blackChecker = "⚫";
const std::string TerminalDisplay::m_whiteChecker = "⚪";
const std::string TerminalDisplay::m_centerPiece = "♚";
const std::string TerminalDisplay::m_leftSideCharacter = "│";
const std::string TerminalDisplay::m_rightSideCharacter = "│";
const std::vector<std::string> TerminalDisplay::m_extraCheckers 
= {"","","","","","","⑥","⑦","⑧","⑨","⑩","⑪","⑫","⑬","⑭","⑮"};


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

void TerminalDisplay::checkerDisplay(
	const Board & board,
	int yCur,
	int xCur, // 25 and -25 are the bottom player and top player's bars respectively
	int yMax,
	bool posPlayerOnBottom,
	std::ostream &outStream
	) {

	outStream << " ";

	int posx;
	int negx;

	// for bar checkers
	if (xCur == 25 || xCur == -25) {
		posx = 24;
		negx = 24;
	} else if (posPlayerOnBottom) {
		posx = xCur-1;
		negx = (25-xCur)-1;
	} else {
		posx = (25-xCur)-1;
		negx = xCur-1;
	}

	if (xCur == 25) { // bottom bar
		if (posPlayerOnBottom) {
			if (board.positiveCheckers(posx) >= yCur) {
				if (yCur == yMax && board.positiveCheckers(posx) > yMax) {
					outStream << m_extraCheckers[board.positiveCheckers(posx)];
				} else {
					outStream << m_blackChecker;
				}		
			} else {
				outStream << " ";
			}
		} else {
			if (board.negativeCheckers(negx) >= yCur) {
				if (yCur == yMax && board.negativeCheckers(negx) > yMax) {
					outStream << m_extraCheckers[board.negativeCheckers(negx)];
				} else {
					outStream << m_whiteChecker;
				}
			} else {
				outStream << " ";
			}
		}
	} else if (xCur == -25) { // top bar
		if (posPlayerOnBottom) {
			if (board.negativeCheckers(negx) >= yCur) {
				if (yCur == yMax && board.negativeCheckers(negx) > yMax) {
					outStream << m_extraCheckers[board.negativeCheckers(negx)];
				} else {
					outStream << m_whiteChecker;
				}		
			}
			else { 
				outStream << " ";
			}
		} else {
			if (board.positiveCheckers(posx) >= yCur) {
				if (yCur == yMax && board.positiveCheckers(posx) > yMax) {
					outStream << m_extraCheckers[board.positiveCheckers(posx)];
				} else {
					outStream << m_blackChecker;
				}				
			} else {
				outStream << " ";
			}
		}		
	} else if (board.positiveCheckers(posx) >= yCur) {
		if (yCur == yMax && board.positiveCheckers(posx) > yMax) {
			outStream << m_extraCheckers[board.positiveCheckers(posx)];
		} else {
			outStream << m_blackChecker;
		}
	} else if (board.negativeCheckers(negx) >= yCur) {
		if (yCur == yMax && board.negativeCheckers(negx) > yMax) {
			outStream << m_extraCheckers[board.negativeCheckers(negx)];
		} else {
			outStream << m_whiteChecker;
		}
	} else {
		outStream << " ";
	}

	outStream << " ";
}

void TerminalDisplay::showBoard(const GameState & gameState, std::ostream &outStream) {

	const Board & board = gameState.board();
	bool posPlayerOnBottom = gameState.isPositivePlayerOnTurn();

	int positiveCheckersBornOff = board.numPositiveCheckersBornOff();
	int negativeCheckersBornOff = board.numNegativeCheckersBornOff();

	int posPipCount = board.positivePipCount();
	int negPipCount = board.negativePipCount();

	outStream << " ┌13─14─15─16─17─18─┬───┬19─20─21─22─23─24─┐ ";
	outStream << (posPlayerOnBottom ? negPipCount : posPipCount);
	outStream << std::endl;

	int ymin = 1;
	int ymax = 5;
	for (int ytop=ymin;ytop<=ymax;ytop++) {
		outStream << " ";
		outStream << m_leftSideCharacter;

		for (int x=13;x<=18;x++) {
			checkerDisplay(board,ytop,x,ymax,posPlayerOnBottom,outStream);
		}

		// checkers on bar
		outStream << m_rightSideCharacter;
		checkerDisplay(board,ytop,-25,ymax,posPlayerOnBottom,outStream);
		outStream << m_leftSideCharacter;

		for (int x=19;x<=24;x++) {
			checkerDisplay(board,ytop,x,ymax,posPlayerOnBottom,outStream);
		}

		outStream << m_rightSideCharacter;
		outStream << " ";

		// born off checkers
		std::string topBornOffChar;
		int topPlayerNumBornOff;
		if (posPlayerOnBottom) { 
			topBornOffChar = m_whiteChecker;
			topPlayerNumBornOff = negativeCheckersBornOff;
		} else {
			topBornOffChar = m_blackChecker;
			topPlayerNumBornOff = positiveCheckersBornOff;
		} 

		for (int xbar=0;xbar<3;xbar++) {
			if (topPlayerNumBornOff >= xbar*5 + ytop) {
				outStream << topBornOffChar;
			} else {
				outStream << " ";
			}
		}
		
		outStream << std::endl;
	}

	outStream << " ";
	outStream << m_rightSideCharacter;
	outStream << "                  ";
	outStream << m_leftSideCharacter;
	outStream << " " << m_centerPiece << " ";
	outStream << m_leftSideCharacter;
	outStream << "                  ";
	outStream << m_rightSideCharacter;
	outStream << std::endl;

	for (int ybottom=ymax;ybottom>=ymin;ybottom--) {
		outStream << " ";
		outStream << m_leftSideCharacter;

		for (int x=12;x>=7;x--) {
			checkerDisplay(board,ybottom,x,ymax,posPlayerOnBottom,outStream);
		}

		// checkers on bar
		outStream << m_rightSideCharacter;
		checkerDisplay(board,ybottom,25,ymax,posPlayerOnBottom,outStream);
		outStream << m_leftSideCharacter;

		for (int x=6;x>=1;x--) {
			checkerDisplay(board,ybottom,x,ymax,posPlayerOnBottom,outStream);
		}

		outStream << m_rightSideCharacter;
		outStream << " ";

		// born off checkers
		std::string bottomBornOffChar;
		int bottomPlayerNumBornOff;
		if (posPlayerOnBottom) { 
			bottomBornOffChar = m_blackChecker;
			bottomPlayerNumBornOff = positiveCheckersBornOff;
		} else {
			bottomBornOffChar = m_whiteChecker;
			bottomPlayerNumBornOff = negativeCheckersBornOff;
		} 

		for (int xbar=0;xbar<3;xbar++) {
			if (bottomPlayerNumBornOff >= xbar*5 + ybottom) {
				outStream << bottomBornOffChar;
			} else {
				outStream << " ";
			}
		}

		outStream << std::endl;
	}

	const std::vector<unsigned int> &dice = gameState.dice();

	outStream << " └12─11─10──9──8──7─┴───┴─6──5──4──3──2──1─┘ ";
	outStream << (posPlayerOnBottom ? posPipCount : negPipCount);
	outStream << " ";
	// status of player on move
	if (dice[0] == 0) {
		outStream << "Roll or Double";
	} else {
		outStream << "Rolled: " << dice[0] << " " << dice[1];
	}
	outStream << std::endl;

}