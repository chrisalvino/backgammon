
#ifndef BOARD_H__
#define BOARD_H__

#include <vector>
#include "gametype.h"

/*
 * Class intended to represent the checkers only!
 * The rest of the game state is in the GameState class.
 */

 namespace zeno {

  class Board {

  public:
    Board(GameType gametype=GameType::BACKGAMMON);
    
    ~Board();
    
    Board(const Board &rhs);
    
    Board & operator=(const Board &rhs);
    
  public:
    void setUpBackgammonCheckers();
    void setUpNackgammonCheckers();
    void setUpHypergammonCheckers();
    int positiveCheckers(int position) const { return m_boardPos[position]; }
    int negativeCheckers(int position) const { return m_boardNeg[position]; }

    int numPositiveCheckersOnBoardOrBar() const;
    int numNegativeCheckersOnBoardOrBar() const;

    int numPositiveCheckersBornOff() const;
    int numNegativeCheckersBornOff() const;

    bool moveChecker(int initialPos, bool positivePlayer, int numPositions);
    bool isMoveLegal(int initialPos, bool positivePlayer, int numPositions);

    int positivePipCount() const;
    int negativePipCount() const;
     
  private:
    static int pipCount(const std::vector<int> &checkers);
    void clearBoard();

  private:
    std::vector<int> m_boardPos;
    std::vector<int> m_boardNeg;
    static const int NUM_POSITIONS;
    int m_totalPosCheckers;
    int m_totalNegCheckers;
  };

}

#endif // BOARD_H__
