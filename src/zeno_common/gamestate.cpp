
#include <deque>
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <limits>
#include "../display/terminaldisplay.h"
#include "stdlib.h"
#include "gamestate.h"

using namespace zeno;

const unsigned int GameState::POS_PLAYER = 0;
const unsigned int GameState::NEG_PLAYER = 1;
const unsigned int GameState::NEITHER_PLAYER = 2;

GameState::GameState() :
m_dice({0,0}),
m_cubeValue(1),
m_score({0,0}),
m_numGames(0),
m_meanScore(0.0),
m_squaredSumOfScoreMinusMean(0.0),
m_playerOnTurn(NEITHER_PLAYER),
m_cubeOwner(NEITHER_PLAYER),
m_gameType(GameType::BACKGAMMON),
m_currentlyDoubled(false),
m_gameFinished(false),
m_readyForRoll(false) {

}

GameState::~GameState() {

}

GameState::GameState(const GameState & rhs) : 
m_board(rhs.m_board),
m_dice(rhs.m_dice),
m_cubeValue(rhs.m_cubeValue),
m_score(rhs.m_score),
m_numGames(rhs.m_numGames),
m_meanScore(rhs.m_meanScore),
m_squaredSumOfScoreMinusMean(rhs.m_squaredSumOfScoreMinusMean),
m_playerOnTurn(rhs.m_playerOnTurn),
m_cubeOwner(rhs.m_cubeOwner),
m_gameType(rhs.m_gameType),
m_currentlyDoubled(rhs.m_currentlyDoubled),
m_gameFinished(rhs.m_gameFinished),
m_readyForRoll(rhs.m_readyForRoll) {

}

GameState & GameState::operator=(const GameState &rhs) {
	if (this == &rhs) {
		return *this;		
	}

	this->m_board = rhs.m_board;
	this->m_dice = rhs.m_dice;
	this->m_cubeValue = rhs.m_cubeValue;
	this->m_score = rhs.m_score;
	this->m_numGames = rhs.m_numGames;
	this->m_meanScore = rhs.m_meanScore;
	this->m_squaredSumOfScoreMinusMean = rhs.m_squaredSumOfScoreMinusMean;
	this->m_playerOnTurn = rhs.m_playerOnTurn;
	this->m_cubeOwner = rhs.m_cubeOwner;
	this->m_gameType = rhs.m_gameType;
	this->m_currentlyDoubled = rhs.m_currentlyDoubled;
	this->m_gameFinished = rhs.m_gameFinished;
	this->m_readyForRoll = rhs.m_readyForRoll;

	return *this;
}

bool GameState::operator==(const GameState & rhs) const {
	return 
	m_board == rhs.m_board && 
	m_dice == rhs.m_dice &&
	m_cubeValue == rhs.m_cubeValue &&
	m_score[0] == rhs.m_score[0] &&
	m_score[1] == rhs.m_score[1] &&
	m_numGames == rhs.m_numGames &&
	m_meanScore == rhs.m_meanScore &&
	m_squaredSumOfScoreMinusMean == rhs.m_squaredSumOfScoreMinusMean &&
	m_playerOnTurn == rhs.m_playerOnTurn &&
	m_cubeOwner == rhs.m_cubeOwner &&
	m_gameType == rhs.m_gameType &&
	m_currentlyDoubled == rhs.m_currentlyDoubled &&
	m_gameFinished == rhs.m_gameFinished &&
	m_readyForRoll == rhs.m_readyForRoll;
}

void GameState::initializeBackgammon(unsigned int playerActingFirst, int initialCubeValue) {
	m_board.setUpBackgammonCheckers();
	m_playerOnTurn = playerActingFirst;
	m_cubeValue = initialCubeValue;
	setBooleanStates(false, // not currently doubled 
			false, // game not finished
			true); // ready for roll
	m_gameType = GameType::BACKGAMMON;
}

void GameState::initializeNackgammon(unsigned int playerActingFirst, int initialCubeValue) {
	m_board.setUpNackgammonCheckers();
	m_playerOnTurn = playerActingFirst;
	m_cubeValue = initialCubeValue;
	setBooleanStates(false, // not currently doubled 
			false, // game not finished
			true); // ready for roll	
	m_gameType = GameType::NACKGAMMON;
}

void GameState::initializeHypergammon(unsigned int playerActingFirst, int initialCubeValue) {
	m_board.setUpHypergammonCheckers();
	m_playerOnTurn = playerActingFirst;
	m_cubeValue = initialCubeValue;	
	setBooleanStates(false, // not currently doubled 
			false, // game not finished
			true); // ready for roll	
	m_gameType = GameType::HYPERGAMMON;
}

void GameState::setDiceRoll(unsigned int die1, unsigned int die2) {
	m_dice[0] = die1;
	m_dice[1] = die2;
	m_readyForRoll = false;
}

void GameState::incrementPositiveScore(unsigned int pointsWon) {
	m_numGames += 1;
	m_score[POS_PLAYER] += pointsWon;
	double delta = (double)pointsWon - m_meanScore;
	m_meanScore += delta / m_numGames;	
	m_squaredSumOfScoreMinusMean += delta*(pointsWon - m_meanScore);
}

void GameState::incrementNegativeScore(unsigned int pointsWon) {
	m_numGames += 1;
	m_score[NEG_PLAYER] += pointsWon;
	double delta = -((double)pointsWon) - m_meanScore;
	m_meanScore += delta / m_numGames;
	m_squaredSumOfScoreMinusMean += delta*(-((double)pointsWon) - m_meanScore);
}

double GameState::pointsPerGame() const {
	return m_meanScore;
}

double GameState::variance() const {
	if (m_numGames < 2) {
		return std::numeric_limits<double>::quiet_NaN();
	} else {
		return m_squaredSumOfScoreMinusMean / (m_numGames - 1);
	}
}

void GameState::setDiceUnrolled() {
	m_dice[0] = 0;
	m_dice[1] = 0;
}

unsigned int GameState::oppositePlayer(unsigned int player) {
	return player == POS_PLAYER ? NEG_PLAYER : POS_PLAYER;
}

void GameState::movePosChecker(int initialPos, int numPositions) {
	m_board.movePosChecker(initialPos, numPositions);
}

void GameState::moveNegChecker(int initialPos, int numPositions) {
	m_board.moveNegChecker(initialPos, numPositions);
}

struct GameStateAndDiceToMove {
public:
	GameStateAndDiceToMove(const GameState & gameState, const std::vector<unsigned int> & diceToMove) :
	m_gameState(gameState),
	m_diceToMove(diceToMove) {

	}

	GameStateAndDiceToMove(const GameStateAndDiceToMove & rhs) :
	m_gameState(rhs.m_gameState),
	m_diceToMove(rhs.m_diceToMove) {

	}	

	GameState m_gameState;
	std::vector<unsigned int> m_diceToMove;
	friend struct std::hash<GameStateAndDiceToMove>;
	bool operator==(const GameStateAndDiceToMove & rhs) const {
		return m_diceToMove == rhs.m_diceToMove && m_gameState == rhs.m_gameState;
	}
};

namespace std {
template<> struct hash<GameStateAndDiceToMove> {
	size_t operator()(const GameStateAndDiceToMove &gameStateAndDiceToMove) const {
		size_t retval = std::hash<GameState>()(gameStateAndDiceToMove.m_gameState);
		auto iteEnd = gameStateAndDiceToMove.m_diceToMove.end();
		for (auto ite = gameStateAndDiceToMove.m_diceToMove.begin(); ite != iteEnd; ++ite) {
			retval += 31 * retval + std::hash<unsigned int>()(*ite);
		}
		return retval;
	}
};
}

std::vector<GameState> GameState::possibleMoves() const {
	std::vector<GameState> result;

	if (m_currentlyDoubled) {
	    /////////////////////////////////
		//// return take state
		/////////////////////////////////
		GameState takeGameState(*this);
		takeGameState.m_cubeValue *= 2;
		takeGameState.m_cubeOwner = m_playerOnTurn;
		takeGameState.m_playerOnTurn = oppositePlayer(m_playerOnTurn);
		takeGameState.setBooleanStates(
			false, // no longer currently doubled
			false, // game not finished
			true  // ready for the next players roll
			);
		takeGameState.setDiceUnrolled();
		result.push_back(takeGameState);

	    /////////////////////////////////		
		//// return pass state (doubling player wins value of cube)
		/////////////////////////////////
		GameState passGameState(*this);
		passGameState.setBooleanStates(
			false, // no longer currently doubled
			true,  // game finished
			false  // not ready for the next players roll
			);
		passGameState.setDiceUnrolled();
		if(passGameState.m_playerOnTurn == POS_PLAYER) {
			passGameState.incrementNegativeScore(passGameState.m_cubeValue);
		} else {
			passGameState.incrementPositiveScore(passGameState.m_cubeValue);
		}
		result.push_back(passGameState);

	} else if (!m_readyForRoll && m_dice[0] == 0) {
	    /////////////////////////////////
		//// ready for roll
		/////////////////////////////////		
		GameState rollGameState(*this);
		rollGameState.setBooleanStates(
			false, // not currently doubled
			false, // game not finished
			true   // ready for the next players roll
			);		
		rollGameState.setDiceUnrolled();
		result.push_back(rollGameState);

		if (m_cubeOwner != oppositePlayer(m_playerOnTurn)) {
	    	/////////////////////////////////
			//// offer a double
			/////////////////////////////////
			GameState doubleOfferedGameState(*this);
			doubleOfferedGameState.togglePlayerOnTurn();
			doubleOfferedGameState.setBooleanStates(
			true,  // currently doubled
			false, // game not finished
			false  // not ready for the next players roll
			);			
			doubleOfferedGameState.setDiceUnrolled();
			// make the cube owner be the other player
			//result.push_back(doubleOfferedGameState);
		}

	} else if (m_dice[0] != 0) {
		std::vector<unsigned int> diceToMove;
		if (m_dice[0] == m_dice[1]) {
			for (int i=0;i<4;++i) {
				diceToMove.push_back(m_dice[0]);
			}
		} else {
			diceToMove.push_back(m_dice[0]);
			diceToMove.push_back(m_dice[1]);
		}

		// sort dice (to make state space smaller)
		std::sort(diceToMove.begin(),diceToMove.end());

		GameState currentGameState(*this);
		std::deque<GameStateAndDiceToMove> statesToProcess;
		std::unordered_set<GameStateAndDiceToMove, std::hash<GameStateAndDiceToMove>> statesAlreadyAdded; 
		GameStateAndDiceToMove initialgsadtm(currentGameState,diceToMove);

		statesAlreadyAdded.insert(initialgsadtm);
		statesToProcess.push_back(initialgsadtm);

		unsigned int minDiceRemaining = diceToMove.size();

		// size of statesToProcess is growing
		for (int stateInd = 0; stateInd < statesToProcess.size(); ++stateInd) {
			
			// we'll grab an unprocessed game state and spawn a number of 
			// possible resulting game states from it
			GameStateAndDiceToMove gsadtm(statesToProcess[stateInd]);

			int diceIndex = 0;
			for (auto ite = gsadtm.m_diceToMove.begin();ite != gsadtm.m_diceToMove.end();ite++, diceIndex++) {

				unsigned int dieUnderConsideration = *ite;

				GameStateAndDiceToMove considered_gasdtm(gsadtm);

				if (m_playerOnTurn==POS_PLAYER) {
					int minInitialPosition;
					int maxInitialPosition;

					if (considered_gasdtm.m_gameState.board().posPlayerHasCheckersOnBar()) {
						minInitialPosition = Board::BAR_POSITION;
						maxInitialPosition = Board::BAR_POSITION;
					} else {
						minInitialPosition = 0;
						maxInitialPosition = Board::BAR_POSITION - 1;
					}
					for (int i = minInitialPosition;
						i <= maxInitialPosition;
						++i) {

						if (considered_gasdtm.m_gameState.board().isPosMoveLegal(i, dieUnderConsideration)) {

						// form new gasdtm from it where that position is moved
							GameState candidateGameState(considered_gasdtm.m_gameState);
							candidateGameState.movePosChecker(i, dieUnderConsideration);

						// remove die roll too
							std::vector<unsigned int> candidateDice = gsadtm.m_diceToMove;
							candidateDice.erase(candidateDice.begin() + diceIndex);

							GameStateAndDiceToMove candidate_gasdtm(candidateGameState,candidateDice);

						// only add it if it's not already been added
							if (statesAlreadyAdded.find(candidate_gasdtm) == statesAlreadyAdded.end()) {
								statesAlreadyAdded.insert(candidate_gasdtm);
								statesToProcess.push_back(candidate_gasdtm);

								if (candidateDice.size() < minDiceRemaining) {
									minDiceRemaining = candidateDice.size();
								}
							}
						} 
					}
				} else {
					int minInitialPosition;
					int maxInitialPosition;

					if (considered_gasdtm.m_gameState.board().negPlayerHasCheckersOnBar()) {
						minInitialPosition = Board::BAR_POSITION;
						maxInitialPosition = Board::BAR_POSITION;
					} else {
						minInitialPosition = 0;
						maxInitialPosition = Board::BAR_POSITION - 1;
					}
					for (int i = minInitialPosition;
						i <= maxInitialPosition;
						++i) {
						if (considered_gasdtm.m_gameState.board().isNegMoveLegal(i, dieUnderConsideration)) {
						// form new gasdtm from it where that position is moved
							GameState candidateGameState = considered_gasdtm.m_gameState;
							candidateGameState.moveNegChecker(i, dieUnderConsideration);

						// remove die roll too
							std::vector<unsigned int> candidateDice = gsadtm.m_diceToMove;
							candidateDice.erase(candidateDice.begin() + diceIndex);

							GameStateAndDiceToMove candidate_gasdtm(candidateGameState,candidateDice);

						// only add it if it's not already been added
							if (statesAlreadyAdded.find(candidate_gasdtm) == statesAlreadyAdded.end()) {
								statesAlreadyAdded.insert(candidate_gasdtm);
								statesToProcess.push_back(candidate_gasdtm);

								if (candidateDice.size() < minDiceRemaining) {
									minDiceRemaining = candidateDice.size();
								}								
							}
						} 
					}				
				}
			}
		}

		// go through set and only take resulting plays where either the game is finished
		// that is all checkers have been born off, or the the DiceToMove.size() == minDiceRemaining
		for (int stateInd = 0; stateInd < statesToProcess.size(); ++stateInd) {
			if (statesToProcess[stateInd].m_diceToMove.size() == minDiceRemaining) {
				GameState gs = statesToProcess[stateInd].m_gameState;
				bool gameFinished = false;
				unsigned int winner = NEITHER_PLAYER;
				bool isGammon = false;
				bool isBackgammon = false;
				if (m_playerOnTurn == POS_PLAYER && gs.board().positivePipCount()==0) {
					gameFinished = true;
					winner = POS_PLAYER;
					if (gs.board().numNegativeCheckersBornOff() == 0) {
						isGammon = true;
						if (gs.board().negativeCheckersInPositiveHomeBoardOrBar()) {
							isBackgammon = true;
						}
					}					
				}
				if (m_playerOnTurn == NEG_PLAYER && gs.board().negativePipCount()==0) {
					gameFinished = true;
					winner = NEG_PLAYER;
					if (gs.board().numPositiveCheckersBornOff() == 0) {
						isGammon = true;
						if (gs.board().positiveCheckersInNegativeHomeBoardOrBar()) {
							isBackgammon = true;
						}						
					}						
				}
				gs.setBooleanStates(
					false,        // not currently doubled 
			 		gameFinished, // only finished if move results in 0 pip count
					false);       // not ready for roll
				if (gameFinished) {
					unsigned int wonAmount = gs.m_cubeValue * (1 + (isGammon ? 1 : 0) + (isBackgammon ? 1 : 0));					
					if(winner == POS_PLAYER) {
						gs.incrementPositiveScore(wonAmount);
					} else {
						gs.incrementNegativeScore(wonAmount);
					}					
				}
				gs.togglePlayerOnTurn();
				gs.setDiceUnrolled();
				result.push_back(gs);
			}
		}

	}
	


	return result;
}
