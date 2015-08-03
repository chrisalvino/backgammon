
#ifndef GAME_H__
#define GAME_H__

#include "board.h"
#include "player.h"

namespace zeno {

	class Game {

	public:	
		Game();

		~Game();

		void setPlayer1(Player *player);
		void setPlayer2(Player *player);

		void startNewGame();
		void move();

	private:
		bool m_Player1sTurn;
		Board m_Board;
		Player *m_player1;
		Player *m_player2;

	private:
		Game(const Game & rhs);

		Game & operator=(const Game & rhs);
	};

}

#endif // GAME_H__