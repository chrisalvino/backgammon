
#ifndef CHECKERTESTS_H__
#define CHECKERTESTS_H__

namespace zeno {
	
	bool comeOffFromBarTest() {
		GameState gameState;
		gameState.initializeBackgammon(GameState::POS_PLAYER, 1);	
		gameState.board().clearBoard();
		gameState.board().setPositiveCheckers(0,2);
		gameState.board().setPositiveCheckers(1,2);
		gameState.board().setPositiveCheckers(2,2);
		gameState.board().setPositiveCheckers(3,2);
		gameState.board().setPositiveCheckers(4,2);
		gameState.board().setPositiveCheckers(5,2);
		gameState.board().setNegativeCheckers(Board::BAR_POSITION,1);
		gameState.setNegPlayerOnTurn();
		for (int i = 1;i <= 6;++i) {
			gameState.setDiceRoll(i,i);
			std::vector<GameState> moves = gameState.possibleMoves();
			if (moves.size() != 1 || moves[0].board().negativeCheckers(Board::BAR_POSITION) != 1) {
				return false;
			}
		}
		return true;
	}
}

#endif  // CHECKERTESTS_H__