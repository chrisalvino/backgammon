
#ifndef PLAYER_H__
#define PLAYER_H__

#include <vector>
#include "board.h"
#include "evaluation.h"

namespace zeno {

    class Player {
    	
    public:
    	Player();

    	virtual ~Player();

    	virtual int chooseMove(std::vector<Board> possibleBoards) = 0;
    
    private:
    	Player(const Player &rhs);

    	Player & operator=(const Player &rhs);
    };

}

#endif // PLAYER_H__