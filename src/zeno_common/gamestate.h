
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

		bool operator==(const GameState & rhs) const;

		const Board & board() const { return m_board; }

		void initializeBackgammon(unsigned int playerActingFirst, int initialCubeValue = 1);
		void initializeNackgammon(unsigned int playerActingFirst, int initialCubeValue = 1);
		void initializeHypergammon(unsigned int playerActingFirst, int initialCubeValue = 1);

		void movePosChecker(int initialPos, int numPositions);
		void moveNegChecker(int initialPos, int numPositions);

		bool isPositivePlayerOnTurn() const { return (m_playerOnTurn == POS_PLAYER); }
		bool isFirstMove() const { return m_firstMove; }
		void finalizeMove();
		void togglePlayerOnTurn() { m_playerOnTurn = oppositePlayer(m_playerOnTurn); };
		static unsigned int oppositePlayer(unsigned int player);
		void setDiceRoll(unsigned int die1, unsigned int die2);
		const std::vector<unsigned int> & dice() const { return m_dice; }

		GameType gameType() const { return m_gameType; }

		bool isGameFinished() const { return m_gameFinished; }

		bool isCurrentlyDoubled() { return m_currentlyDoubled; }

		bool isCubeCentered() const { return m_cubeOwner == NEITHER_PLAYER; }
		bool posPlayerOwnsCube() const { return m_cubeOwner == POS_PLAYER; }
		bool negPlayerOwnsCube() const { return m_cubeOwner == NEG_PLAYER; }
		int cubeValue() const { return m_cubeValue; }

		std::vector<GameState> possibleMoves() const;

		static const unsigned int POS_PLAYER;
		static const unsigned int NEG_PLAYER;
		static const unsigned int NEITHER_PLAYER;

		friend struct std::hash<GameState>;

	private:
		// force all states to be set
		void setBooleanStates(
			bool currentlyDoubled, 
			bool gameFinished,
			bool firstMove,
			bool readyForRoll) {
			m_currentlyDoubled = currentlyDoubled;
			m_gameFinished = gameFinished;
			m_firstMove = firstMove;
			m_readyForRoll = readyForRoll;
		}

	private:
		Board m_board;
		std::vector<unsigned int> m_dice;
		int m_cubeValue;
		std::vector<unsigned int> m_score;
		unsigned int m_playerOnTurn;		// player whose decision it is
		unsigned int m_cubeOwner;
		GameType m_gameType;
		bool m_currentlyDoubled;			// it's doubled and waiting for take/pass     
		bool m_gameFinished;
		bool m_firstMove;
		bool m_readyForRoll;				// player has decided to roll


	// may include the state below at a later point
	// but not doing it now for simplicity
	// 
	// intentionally leaving out anything related to match play
    // int fResigned;          // will handle resignation later
    // int fResignationDeclined;  
    // int fDoubled;              
    // int fCrawford;              // match
    // int fPostCrawford;          // match
    // int nMatchTo;               // match      
    // unsigned int cBeavers;      // will do later
    // bgvariation bgv;            // will do later
    // int fCubeUse;               // will do later
    // int fJacoby;                // will do later

	};

}

#include "gamestate.hxx"

#endif // GAMESTATE_H__