
#include <stdlib.h>
#include <unistd.h>
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

		//usleep(50000);
		// get possible game states for player to consider
		std::vector<GameState> possibleGameStates = m_gameState.possibleMoves();

#if 0
		for (auto ite = possibleGameStates.begin(); ite != possibleGameStates.end() ; ++ite) {
			if (m_pDisplay != 0) {
				m_pDisplay->showBoard(*ite);
			}
		}	
		exit(1);
#endif	

		GameState newGameState;

		// player chooses from possible game states
		if (m_gameState.isPositivePlayerOnTurn()) {
			newGameState = m_pPlayerPos->chooseMove(possibleGameStates);
		} else {
			newGameState = m_pPlayerNeg->chooseMove(possibleGameStates);
		}

		// anything needed for game to update state here
		if (newGameState.isReadyForRoll()) {
			int die1 = m_pDie->getDieRoll();
			int die2 = m_pDie->getDieRoll();		
			newGameState.setDiceRoll(die1,die2);		
		}

		// make this the new game state
		m_gameState = newGameState;
	}

	if (m_pDisplay != 0) {
		m_pDisplay->showBoard(m_gameState);
	}
}

void Game::move() {

}