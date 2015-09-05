
#include <iostream>
#include "game.h"

using namespace zeno;

Game::Game() :
m_pPlayer1(0),
m_pPlayer2(0),
m_pDie(0),
m_automaticDoubles(false),
m_pStreamDisplay(0) {

}

Game::~Game() {
	// m_player1 and m_player2 are only copies of players
	// and should not be deleted
}

void Game::play() {

	// roll dice to decide who goes first
	int posDie; 
	int negDie; 

	int initialCubeValue = 1;
	while (true) {
		posDie = m_pDie->getDieRoll();
		negDie = m_pDie->getDieRoll();
		if (posDie == negDie) {
			if (m_automaticDoubles) {
				initialCubeValue *= 2;
			}
		} else {
			break;
		}
	};

	unsigned int startingPlayer = (posDie > negDie) ? GameState::POS_PLAYER : GameState::NEG_PLAYER ;

	// reset board
	m_gameState.initializeBackgammon(startingPlayer, initialCubeValue);
	m_gameState.setDiceRoll(posDie, negDie);

	while (!m_gameState.isGameFinished()) {
		if (m_pStreamDisplay != 0) {
			m_pStreamDisplay->showBoard(m_gameState,std::cout);
		}

		return;
		if (m_gameState.isFirstMove()) {
			// don't roll dice, dice are provided by initial roll

			m_gameState.setNoLongerFirstMove();
		} else {
				// give opportunity to double, if double, then continue and give
				// opponent chance to respond

				// if no double, then roll dice and move

		}
	}

}

void Game::move() {

}