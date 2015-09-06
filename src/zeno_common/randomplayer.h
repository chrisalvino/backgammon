
#ifndef RANDOMPLAYER_H__
#define RANDOMPLAYER_H__

#include "player.h"

namespace zeno {

	class RandomPlayer : public Player {

	public:
		RandomPlayer();

		virtual ~RandomPlayer();

	public:
		virtual GameState chooseMove(std::vector<GameState> possibleBoards);

	};

}

#endif // RANDOMPLAYER_H__
