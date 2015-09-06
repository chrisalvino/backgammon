
#include <set>
#include <deque>
#include <unordered_set>
#include "gamestate.h"

using namespace zeno;

const unsigned int GameState::POS_PLAYER = 0;
const unsigned int GameState::NEG_PLAYER = 1;
const unsigned int GameState::NEITHER_PLAYER = 2;

namespace std {
template<> struct hash<GameState> {
  size_t operator()(const GameState &gameState) const {

    size_t retval = 0;
    retval += std::hash<Board>()(gameState.m_board);
    retval += 31 * retval + std::hash<unsigned int>()(gameState.m_dice[0]);
    retval += 31 * retval + std::hash<unsigned int>()(gameState.m_dice[1]);
    retval += 31 * retval + std::hash<int>()(gameState.m_cubeValue);
    retval += 31 * retval + std::hash<unsigned int>()(gameState.m_score[0]);
    retval += 31 * retval + std::hash<unsigned int>()(gameState.m_score[1]);
    retval += 31 * retval + std::hash<unsigned int>()(gameState.m_playerOnTurn);
    retval += 31 * retval + std::hash<unsigned int>()(gameState.m_cubeOwner);
    retval += 31 * retval + std::hash<int>()((int)gameState.m_gameType);
    retval += 31 * retval + std::hash<bool>()(gameState.m_currentlyDoubled);
    retval += 31 * retval + std::hash<bool>()(gameState.m_gameFinished);
    retval += 31 * retval + std::hash<bool>()(gameState.m_firstMove);
    retval += 31 * retval + std::hash<bool>()(gameState.m_readyForRoll);
    
    return retval;
  }
};
}

GameState::GameState() :
m_dice({0,0}),
m_cubeValue(1),
m_score({0,0}),
m_playerOnTurn(NEITHER_PLAYER),
m_cubeOwner(NEITHER_PLAYER),
m_gameType(GameType::BACKGAMMON),
m_currentlyDoubled(false),
m_gameFinished(false),
m_firstMove(true),
m_readyForRoll(false) {

}

GameState::~GameState() {

}

GameState::GameState(const GameState & rhs) : 
m_board(rhs.m_board),
m_dice(rhs.m_dice),
m_cubeValue(rhs.m_cubeValue),
m_score(rhs.m_score),
m_playerOnTurn(rhs.m_playerOnTurn),
m_cubeOwner(rhs.m_cubeOwner),
m_gameType(rhs.m_gameType),
m_currentlyDoubled(rhs.m_currentlyDoubled),
m_gameFinished(rhs.m_gameFinished),
m_firstMove(rhs.m_firstMove),
m_readyForRoll(rhs.m_readyForRoll)
{

}

GameState & GameState::operator=(const GameState &rhs) {
	if (this == &rhs) {
		return *this;		
	}

	this->m_board = rhs.m_board;
	this->m_dice = rhs.m_dice;
	this->m_cubeValue = rhs.m_cubeValue;
	this->m_score = rhs.m_score;
	this->m_playerOnTurn = rhs.m_playerOnTurn;
	this->m_cubeOwner = rhs.m_cubeOwner;
	this->m_gameType = rhs.m_gameType;
	this->m_currentlyDoubled = rhs.m_currentlyDoubled;
	this->m_gameFinished = rhs.m_gameFinished;
	this->m_firstMove = rhs.m_firstMove;
	this->m_readyForRoll = rhs.m_readyForRoll;

	return *this;
}

bool GameState::operator==(const GameState & rhs) const {
	return 
	m_board == rhs.m_board && 
	m_dice == rhs.m_dice &&
	m_cubeValue == rhs.m_cubeValue &&
	m_score == rhs.m_score &&
	m_playerOnTurn == rhs.m_playerOnTurn &&
	m_cubeOwner == rhs.m_cubeOwner &&
	m_gameType == rhs.m_gameType &&
	m_currentlyDoubled == rhs.m_currentlyDoubled &&
	m_gameFinished == rhs.m_gameFinished &&
	m_firstMove == rhs.m_firstMove &&
	m_readyForRoll == rhs.m_readyForRoll;
}

void GameState::initializeBackgammon(unsigned int playerActingFirst, int initialCubeValue) {
	m_board.setUpBackgammonCheckers();
	m_playerOnTurn = playerActingFirst;
	m_cubeValue = initialCubeValue;
	m_firstMove = true;
	m_gameType = GameType::BACKGAMMON;
}

void GameState::initializeNackgammon(unsigned int playerActingFirst, int initialCubeValue) {
	m_board.setUpNackgammonCheckers();
	m_playerOnTurn = playerActingFirst;
	m_cubeValue = initialCubeValue;
	m_firstMove = true;
	m_gameType = GameType::NACKGAMMON;
}

void GameState::initializeHypergammon(unsigned int playerActingFirst, int initialCubeValue) {
	m_board.setUpHypergammonCheckers();
	m_playerOnTurn = playerActingFirst;
	m_cubeValue = initialCubeValue;	
	m_firstMove = true;	
	m_gameType = GameType::HYPERGAMMON;
}

void GameState::setDiceRoll(unsigned int die1, unsigned int die2) {
	m_dice[0] = die1;
	m_dice[1] = die2;
}

void GameState::finalizeMove() {
	m_firstMove = false; 
	m_dice[0] = 0;
	m_dice[1] = 0;	
}

unsigned int GameState::oppositePlayer(unsigned int player) {
	return player == POS_PLAYER ? NEG_PLAYER : POS_PLAYER;
}

struct GameStateAndDiceToMove {
	GameState m_gameState;
	std::vector<unsigned int> m_diceToMove;
	friend struct std::hash<GameStateAndDiceToMove>;
	bool operator==(const GameStateAndDiceToMove & rhs) const {
		return m_gameState == rhs.m_gameState && m_diceToMove == rhs.m_diceToMove;
	}
};

namespace std {
template<> struct hash<GameStateAndDiceToMove> {
	size_t operator()(const GameStateAndDiceToMove &gameStateAndDiceToMove) const {
		return 
		//std::hash<Board>()(gameState.m_board)
		std::hash<GameState>()(gameStateAndDiceToMove.m_gameState) ^ 
		std::hash<unsigned int>()(gameStateAndDiceToMove.m_diceToMove[0]);
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
		takeGameState.setBooleanStates(
			false, // no longer currently doubled
			false, // game not finished
			false, // can't possibly be first move
			true   // ready for the next players roll
			);
		result.push_back(takeGameState);

	    /////////////////////////////////		
		//// return pass state (doubling player wins value of cube)
		/////////////////////////////////
		GameState passGameState(*this);
		takeGameState.setBooleanStates(
			false, // no longer currently doubled
			true,  // game finished
			false, // can't possibly be first move
			false  // not ready for the next players roll
			);
		passGameState.m_score[passGameState.m_playerOnTurn == POS_PLAYER ? NEG_PLAYER : POS_PLAYER] += passGameState.m_cubeValue;
		result.push_back(passGameState);

	} else if(m_dice[0] == 0 && m_dice[1] == 0) {
	    /////////////////////////////////
		//// ready for roll
		/////////////////////////////////		
		GameState rollGameState(*this);
		rollGameState.setBooleanStates(
			false, // not currently doubled
			false, // game not finished
			false, // no longer first move
			true   // ready for the next players roll
			);		
		result.push_back(rollGameState);

	    /////////////////////////////////
		//// offer a double
		/////////////////////////////////
		GameState doubleOfferedGameState(*this);
		doubleOfferedGameState.setBooleanStates(
			true,  // currently doubled
			false, // game not finished
			false, // no longer first move
			false  // not ready for the next players roll
			);			
		// make the cube owner be the other player
		doubleOfferedGameState.m_cubeOwner = doubleOfferedGameState.m_playerOnTurn == POS_PLAYER ? NEG_PLAYER : POS_PLAYER;
		result.push_back(doubleOfferedGameState);

	} else {
		std::vector<unsigned int> diceToMove;
		if (m_dice[0] == m_dice[1]) {
			for (int i=0;i<4;++i) {
				diceToMove.push_back(m_dice[0]);
			}
		} else {
			diceToMove.push_back(m_dice[0]);
			diceToMove.push_back(m_dice[1]);
		}

		GameState currentGameState(*this);
		std::unordered_set<GameStateAndDiceToMove, std::hash<GameStateAndDiceToMove>> statesToProcess; 
		GameStateAndDiceToMove initialgsadtm;
		initialgsadtm.m_gameState = currentGameState;
		initialgsadtm.m_diceToMove = diceToMove;

		statesToProcess.insert(initialgsadtm);

		while (!statesToProcess.empty()) {

		}

		// remove duplicates



	}

	return result;
}
