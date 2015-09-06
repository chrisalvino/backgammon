
#ifndef DISPLAY_H__
#define DISPLAY_H__

#include "gamestate.h"
#include <ostream>

namespace zeno {

	class Display {

	public:
		Display() { }

		virtual ~Display() { }

	public:
		virtual void showBoard(const GameState & gs) = 0;

	};

}

#endif // DISPLAY_H__