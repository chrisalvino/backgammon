
#include <iostream>
#include "game.h"

using namespace zeno;

Game::Game() :
m_pPlayerPos(0),
m_pPlayerNeg(0),
m_pDie(0),
m_automaticDoubles(false),
m_pDisplay(0) {

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

	// set up initial game state
	m_gameState.initializeBackgammon(startingPlayer, initialCubeValue);
	m_gameState.setDiceRoll(posDie, negDie);

	while (!m_gameState.isGameFinished()) {
		// display board
		if (m_pDisplay != 0) {
			m_pDisplay->showBoard(m_gameState);
		}

		// get possible game states for player to consider
		std::vector<GameState> possibleGameStates = m_gameState.possibleMoves();

		// player chooses from possible game states
		if (m_gameState.isPositivePlayerOnTurn()) {
			
		} else {
			
		}

		if (m_gameState.isFirstMove()) {
			// don't roll dice, dice are provided by initial roll
			if () {

			} else {

			}

			m_gameState.finalizeMove();
		} else {
			// give opportunity to double, if double, then continue and give
			// opponent chance to respond

			// if no double, then roll dice and move

		}
	}

}

void Game::move() {

}