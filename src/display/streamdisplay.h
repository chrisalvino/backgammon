
#ifndef DISPLAY_H__
#define DISPLAY_H__

#include "gamestate.h"
#include <ostream>

namespace zeno {

	class StreamDisplay {

	public:
		StreamDisplay() { }

		virtual ~StreamDisplay() { }

	public:
		virtual void showBoard(const GameState & gs, std::ostream &outStream) = 0;

	};

}

#endif // TERMINALDISPLAY_H__