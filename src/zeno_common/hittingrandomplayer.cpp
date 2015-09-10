
#include "hittingrandomplayer.h"

#include <stdlib.h>
#include <math.h>

using namespace zeno;

HittingRandomPlayer::HittingRandomPlayer() {

}

HittingRandomPlayer::~HittingRandomPlayer() {
	
}

GameState HittingRandomPlayer::chooseMove(std::vector<GameState> possibleBoards) {	
	unsigned int maxOpponentPipCount = 0;
	for (auto ite = possibleBoards.begin() ; ite != possibleBoards.end() ; ++ite) {
		int curOppPipCount = ite->board().negativePipCount();
		if (curOppPipCount > maxOpponentPipCount) {
			maxOpponentPipCount = curOppPipCount;
		}
	}

	std::vector<GameState> maximumOpponentsPipCountGameStates;
	for (auto ite = possibleBoards.begin() ; ite != possibleBoards.end() ; ++ite) { 
		if (ite->board().negativePipCount() == maxOpponentPipCount) {
			maximumOpponentsPipCountGameStates.push_back(*ite);
		}
	}
	
	// select boards with maximum opponents pip count
	int randInd = floor(drand48() * maximumOpponentsPipCountGameStates.size());
	return maximumOpponentsPipCountGameStates[randInd];
}