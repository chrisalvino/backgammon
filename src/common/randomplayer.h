
#ifndef RANDOMPLAYER_H__
#define RANDOMPLAYER_H__

#include "player.h"

namespace zeno {

	class RandomPlayer : public Player {

	public:
		RandomPlayer();

		virtual ~RandomPlayer();

	public:
		virtual int chooseMove(std::vector<Board> possibleBoards);

	};

}

#endif // RANDOMPLAYER_H__
