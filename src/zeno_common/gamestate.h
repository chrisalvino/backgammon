
#ifndef GAMESTATE_H__
#define GAMESTATE_H__

#include <vector>
#include "board.h"
#include "gametype.h"

namespace zeno {

	class GameState {

	public:
		GameState();

		~GameState();

		GameState(const GameState & rhs);

		GameState & operator=(const GameState &rhs);

		const Board & board() const { return m_board; }

		void initializeBackgammon(unsigned int playerActingFirst, int initialCubeValue = 1);
		void initializeNackgammon(unsigned int playerActingFirst, int initialCubeValue = 1);
		void initializeHypergammon(unsigned int playerActingFirst, int initialCubeValue = 1);

		bool isPositivePlayerOnTurn() const { return (m_playerOnTurn == POS_PLAYER); }
		bool isFirstMove() const { return m_firstMove; }
		void setNoLongerFirstMove() { m_firstMove = false; }
		void setDiceRoll(unsigned int die1, unsigned int die2);
		const std::vector<unsigned int> & dice() const { return m_dice; }

		GameType gameType() const { return m_gameType; }

		bool isGameFinished() const { return m_gameFinished; }

		bool isDoubled() { return m_doubled; }

		static const unsigned int POS_PLAYER;
		static const unsigned int NEG_PLAYER;
		static const unsigned int NEITHER_PLAYER;

	private:
		Board m_board;
		std::vector<unsigned int> m_dice;
		int m_cubeValue;
		std::vector<unsigned int> m_score;
		unsigned int m_numGames;
		unsigned int m_playerOnTurn;		// player whose turn it is
		bool m_doubled;						// it's doubled and waiting for take/pass
		bool m_cubeCentered;      
		unsigned int m_cubeOwner;
		GameType m_gameType;
		bool m_gameFinished;
		bool m_firstMove;


	// may include the state below at a later point
	// but not doing it now for simplicity
	// 
	// intentionally leaving out anything related to match play
    // int fResigned;          // will handle resignation later
    // int fResignationDeclined;  
    // int fDoubled;              
    // int fMove;                  // player on roll 
    // int fCrawford;              // match
    // int fPostCrawford;          // match
    // int nMatchTo;               // match      
    // unsigned int cBeavers;      // will do later
    // bgvariation bgv;            // will do later
    // int fCubeUse;               // will do later
    // int fJacoby;                // will do later

};

}

#endif // GAMESTATE_H__