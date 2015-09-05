
#ifndef STREAMDISPLAY_H__
#define STREAMDISPLAY_H__

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

#endif // STREAMDISPLAY_H__