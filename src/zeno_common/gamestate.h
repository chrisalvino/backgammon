
#ifndef GAMESTATE_H__
#define GAMESTATE_H__

#include <vector>

namespace zeno {

class GameState {

public:
	GameState();

	~GameState();

	GameState(const GameState & rhs);

	GameState & operator=(const GameState &rhs);

private:
	std::vector<unsigned int> m_TanBoard[2];
	std::vector<unsigned int> m_Dice;

};

}

#endif // GAMESTATE_H__