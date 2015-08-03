
#include "game.h"

using namespace zeno;

Game::Game() :
m_Player1sTurn(true),
m_player1(0),
m_player2(0)
{

}

Game::~Game() {
	// m_player1 and m_player2 are only copies of players
	// and should not be deleted
}

void Game::startNewGame() {
	m_Player1sTurn = true;
	m_Board.reset();
}

void Game::move() {
	
}