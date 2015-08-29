
#ifndef BOARD_H__
#define BOARD_H__

#include <vector>

namespace zeno {

    class Board {
    
     public:
      Board();
    
      ~Board();
    
      Board(const Board &rhs);
    
      Board & operator=(const Board &rhs);
    
     public:
      void reset();
      int getPosition(int pos);
      bool moveChecker(int initialPos, bool positivePlayer,  int numPositions);
      bool isMoveLegal(int initialPos, bool positivePlayer,  int numPositions);
    
     private:
      std::vector<int> m_board;
      static const int NUM_POSITIONS;
      int m_numPositiveOnBar;
      int m_numNegativeOnBar;
      int m_numPositiveBornOff;
      int m_numNegativeBornOff;
    };

}

#endif // BOARD_H__
