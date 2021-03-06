
#ifndef GAME_H__
#define GAME_H__

#include <vector>
#include "display/display.h"
#include "gamestate.h"
#include "player.h"
#include "die.h"

namespace zeno {

	class Game {

	public:	
		Game();

		~Game();

		void setPlayerPos(Player *pPlayerPos) { m_pPlayerPos = pPlayerPos; }
		void setPlayerNeg(Player *pPlayerNeg) { m_pPlayerNeg = pPlayerNeg; }
		void setDie(Die *pDie) { m_pDie = pDie; }
		void setDisplay(Display *pDisplay) { m_pDisplay = pDisplay; }

		void play();
		void startNewGame();
		void move();
		double pointsPerGame() { return m_gameState.pointsPerGame(); }
		double standardError() { return sqrt(m_gameState.variance() / m_gameState.numGames()); }
		std::vector<unsigned int> score() { return m_gameState.score(); }

	private:
		GameState m_gameState;
		Player *m_pPlayerPos;
		Player *m_pPlayerNeg;
		Die *m_pDie;
		bool m_automaticDoubles;
		Display * m_pDisplay;

	private:
		Game(const Game & rhs);

		Game & operator=(const Game & rhs);
	};

}

#endif // GAME_H__