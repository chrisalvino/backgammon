
#include "randomplayer.h"

#include <stdlib.h>
#include <math.h>

using namespace zeno;

GameState RandomPlayer::chooseMove(std::vector<GameState> possibleBoards) {	
	int randInd = floor(drand48() * possibleBoards.size());
	return possibleBoards[randInd];
}