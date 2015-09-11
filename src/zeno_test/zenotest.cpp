
#include "gamestate.h"

using namespace zeno;

int main(int argc, char **argv) {

	try {
		GameState gameState;
		gameState.initializeBackgammon(GameState::POS_PLAYER, 1);
		

	} catch (const std::exception &e) {
		return 1;
	}

	return 0;
}