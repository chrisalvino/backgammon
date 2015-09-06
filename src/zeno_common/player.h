
#ifndef PLAYER_H__
#define PLAYER_H__

#include <vector>
#include "gamestate.h"
#include "evaluation.h"

namespace zeno {

    class Player {
    	
    public:
    	Player() { }

    	virtual ~Player() { }

    	virtual GameState chooseMove(std::vector<GameState> possibleBoards) = 0;
    
    private:
    	Player(const Player &rhs);

    	Player & operator=(const Player &rhs);
    };

}

#endif // PLAYER_H__