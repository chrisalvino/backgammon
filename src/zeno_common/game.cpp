
#include "game.h"

using namespace zeno;

Game::Game() :
m_Player1sTurn(true),
m_player1(0),
m_player2(0),
m_die(0),
m_automaticDoubles(false)
{

}

Game::~Game() {
	// m_player1 and m_player2 are only copies of players
	// and should not be deleted
}

void Game::startNewGame(unsigned int numGames) {

	for (unsigned int i=0;i<numGames;++i) {
		// reset board
		m_gameState.initializeBackgammon();

		// roll dice to decide who goes first
		int posDie; 
		int negDie; 

		int initialCubeValue = 1;
		while (true) {
			posDie = m_die->getDieRoll();
			negDie = m_die->getDieRoll();
			if (posDie == negDie) {
				if (automaticDoubles) {
					initialCubeValue *= 2;
				}
			} else {
				break;
			}
		};

		bool isFirstMove = true;
		bool isPosPlayerOnTurn;
		isPosPlayerOnTurn = (posDie > negDie);

		while (!m_gameState.isGameFinished()) {

			if (isFirstMove) {
				// don't roll dice, dice are provided by initial roll

				isFirstMove = false;
			} else {
				// give opportunity to double, if double, then continue and give
				// opponent chance to respond

				// if no double, then roll dice and move

			}
		}
	}


	

}

void Game::move() {

}