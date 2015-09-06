
#ifndef TERMINALDISPLAY_H__
#define TERMINALDISPLAY_H__

#include "display.h"
#include "gamestate.h"
#include <ostream>
#include <string>

namespace zeno {

	class TerminalDisplay : public Display {

	public:
		TerminalDisplay(std::ostream &outStream);

		~TerminalDisplay();

	public:
		void showBoard(const GameState & gs);

	private:
		void checkerDisplay(
			const Board & board,
			int yCur,
			int xCur, // 25 and -25 are the bottom player and top player's bars respectively
			int yMax,
			bool posPlayerOnBottom
			);

		static const std::string m_blackChecker;
		static const std::string m_whiteChecker;
		static const std::string m_centerPiece;
		static const std::string m_leftSideCharacter;
		static const std::string m_rightSideCharacter;
		static const std::vector<std::string> m_extraCheckers;

		std::ostream &m_outStream;

	};

}

#endif // TERMINALDISPLAY_H__