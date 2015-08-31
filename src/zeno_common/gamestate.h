
#ifndef GAMESTATE_H__
#define GAMESTATE_H__

#include <vector>
#include "board.h"

namespace zeno {

	class GameState {

	public:
		GameState();

		~GameState();

		GameState(const GameState & rhs);

		GameState & operator=(const GameState &rhs);

		const Board & getBoard() const { return m_board; }

		void initializeBackgammon();
		void initializeNackgammon();
		void initializeHypergammon();

		bool isPositivePlayerOnTurn() const { return (m_playerOnTurn == POS_PLAYER_INDEX); }

		static const unsigned int POS_PLAYER_INDEX;
		static const unsigned int NEG_PLAYER_INDEX;

	private:
		Board m_board;
		std::vector<unsigned int> m_dice;
		int m_cubeValue;
		std::vector<unsigned int> m_score;
		unsigned int m_numGames;
		unsigned int m_playerOnTurn;
		bool m_isDoubled;
		bool m_cubeCentered;
		unsigned int m_cubeOwner;


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