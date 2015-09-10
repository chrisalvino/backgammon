
#ifndef HITTINGRANDOMPLAYER_H__
#define HITTINGRANDOMPLAYER_H__

#include "player.h"

namespace zeno {

	class HittingRandomPlayer : public Player {

	public:
		HittingRandomPlayer();

		virtual ~HittingRandomPlayer();

	public:
		virtual GameState chooseMove(std::vector<GameState> possibleBoards);

	};

}

#endif // HITTINGRANDOMPLAYER_H__
