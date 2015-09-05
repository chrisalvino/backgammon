
#ifndef GAME_H__
#define GAME_H__

#include "gamestate.h"
#include "player.h"
#include "die.h"

namespace zeno {

	class Game {

	public:	
		Game();

		~Game();

		void setPlayer1(Player *player) { m_player1 = player; }
		void setPlayer2(Player *player) { m_player2 = player; }
		void setDie(Die *die) { m_die = die; }

		void startNewGame();
		void move();

	private:
		bool m_Player1sTurn;
		GameState m_gameState;
		Player *m_player1;
		Player *m_player2;
		Die *m_die;
		bool m_automaticDoubles;

	private:
		Game(const Game & rhs);

		Game & operator=(const Game & rhs);
	};

}

#endif // GAME_H__