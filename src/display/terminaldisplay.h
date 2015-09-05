
#ifndef TERMINALDISPLAY_H__
#define TERMINALDISPLAY_H__

#include "streamdisplay.h"
#include "gamestate.h"
#include <ostream>
#include <string>

namespace zeno {

	class TerminalDisplay : public StreamDisplay {

	public:
		TerminalDisplay();

		~TerminalDisplay();

	public:
		void showBoard(const GameState & gs, std::ostream &outStream);

	private:
		static void checkerDisplay(
			const Board & board,
			int yCur,
			int xCur, // 25 and -25 are the bottom player and top player's bars respectively
			int yMax,
			bool posPlayerOnBottom,
			std::ostream &outStream
			);

		static const std::string m_blackChecker;
		static const std::string m_whiteChecker;
		static const std::string m_centerPiece;
		static const std::string m_leftSideCharacter;
		static const std::string m_rightSideCharacter;
		static const std::vector<std::string> m_extraCheckers;

	};

}

#endif // TERMINALDISPLAY_H__