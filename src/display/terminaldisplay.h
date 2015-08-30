
#ifndef TERMINALDISPLAY_H__
#define TERMINALDISPLAY_H__

#include "gamestate.h"
#include <ostream>

namespace zeno {

	class TerminalDisplay {

	public:
		TerminalDisplay();

		~TerminalDisplay();

	public:
		void showBoard(const GameState & gs, std::ostream &outStream);


	};

}

#endif // TERMINALDISPLAY_H__