
#ifndef BOARD_H__
#define BOARD_H__

#include <vector>

/*
 * Class intended to represent the checkers only!
 * The rest of the game state is in the GameState class.
 */

 namespace zeno {

  class Board {

  public:
    Board();
    
    ~Board();
    
    Board(const Board &rhs);
    
    Board & operator=(const Board &rhs);
    
  public:
    void reset();
    int getPosPlayerCheckers(int position) const { return m_boardPos[position]; }
    int getNegPlayerCheckers(int position) const { return m_boardNeg[position]; }
    bool moveChecker(int initialPos, bool positivePlayer, int numPositions);
    bool isMoveLegal(int initialPos, bool positivePlayer, int numPositions);
    
  private:
    std::vector<int> m_boardPos;
    std::vector<int> m_boardNeg;
    static const int NUM_POSITIONS;
  };

}

#endif // BOARD_H__
