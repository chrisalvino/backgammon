
#include "gamestate.h"

using namespace zeno;

const unsigned int GameState::POS_PLAYER_INDEX = 0;
const unsigned int GameState::NEG_PLAYER_INDEX = 1;

GameState::GameState() {
	m_dice.resize(2);
	m_dice[0] = 0;
	m_dice[1] = 0;
	m_score.resize(2);
	m_score[POS_PLAYER_INDEX] = 0;
	m_score[NEG_PLAYER_INDEX] = 0;
	m_playerOnTurn = POS_PLAYER_INDEX;
}

GameState::~GameState() {

}

GameState::GameState(const GameState & rhs) : 
m_board(rhs.m_board) ,
m_dice(rhs.m_dice),
m_cubeValue(rhs.m_cubeValue),
m_score(rhs.m_score),
m_numGames(rhs.m_numGames),
m_playerOnTurn(rhs.m_playerOnTurn),
m_isDoubled(rhs.m_isDoubled),
m_cubeCentered(rhs.m_cubeCentered),
m_cubeOwner(rhs.m_cubeOwner)
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

	return *this;
}

void GameState::initializeBackgammon() {
	m_board.setUpBackgammonCheckers();
}

void GameState::initializeNackgammon() {
	m_board.setUpNackgammonCheckers();
}

void GameState::initializeHypergammon() {
	m_board.setUpHypergammonCheckers();
}

