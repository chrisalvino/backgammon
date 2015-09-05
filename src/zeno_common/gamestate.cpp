
#include "gamestate.h"

using namespace zeno;

const unsigned int GameState::POS_PLAYER = 0;
const unsigned int GameState::NEG_PLAYER = 1;
const unsigned int GameState::NEITHER_PLAYER = 2;

GameState::GameState() :
m_dice({0,0}),
m_cubeValue(1),
m_score({0,0}),
m_numGames(1),
m_playerOnTurn(NEITHER_PLAYER),
m_doubled(false),
m_cubeCentered(true),
m_cubeOwner(NEITHER_PLAYER),
m_gameType(GameType::BACKGAMMON),
m_gameFinished(false),
m_firstMove(true) {

}

GameState::~GameState() {

}

GameState::GameState(const GameState & rhs) : 
m_board(rhs.m_board),
m_dice(rhs.m_dice),
m_cubeValue(rhs.m_cubeValue),
m_score(rhs.m_score),
m_numGames(rhs.m_numGames),
m_playerOnTurn(rhs.m_playerOnTurn),
m_doubled(rhs.m_doubled),
m_cubeCentered(rhs.m_cubeCentered),
m_cubeOwner(rhs.m_cubeOwner),
m_gameType(rhs.m_gameType),
m_gameFinished(rhs.m_gameFinished),
m_firstMove(rhs.m_firstMove)
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
	this->m_numGames = rhs.m_numGames;
	this->m_playerOnTurn = rhs.m_playerOnTurn;
	this->m_doubled = rhs.m_doubled;
	this->m_cubeCentered = rhs.m_cubeCentered;
	this->m_cubeOwner = rhs.m_cubeOwner;
	this->m_gameType = rhs.m_gameType;
	this->m_gameFinished = rhs.m_gameFinished;
	this->m_firstMove = rhs.m_firstMove;

	return *this;
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

