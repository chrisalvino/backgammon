
#ifndef GAME_H__
#define GAME_H__

#include "display/streamdisplay.h"
#include "gamestate.h"
#include "player.h"
#include "die.h"

namespace zeno {

	class Game {

	public:	
		Game();

		~Game();

		void setPlayer1(Player *pPlayer) { m_pPlayer1 = pPlayer; }
		void setPlayer2(Player *pPlayer) { m_pPlayer2 = pPlayer; }
		void setDie(Die *pDie) { m_pDie = pDie; }
		void setDisplay(StreamDisplay *pStreamDisplay) { m_pStreamDisplay = pStreamDisplay; }

		void play();
		void startNewGame();
		void move();

	private:
		GameState m_gameState;
		Player *m_pPlayer1;
		Player *m_pPlayer2;
		Die *m_pDie;
		bool m_automaticDoubles;
		StreamDisplay * m_pStreamDisplay;

	private:
		Game(const Game & rhs);

		Game & operator=(const Game & rhs);
	};

}

#endif // GAME_H__