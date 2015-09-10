
#ifndef BOARD_H__
#define BOARD_H__

#include <vector>
#include <unordered_set>
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

    bool operator==(const Board & rhs) const; 

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

    bool positiveCheckersInNegativeHomeBoardOrBar() const;
    bool negativeCheckersInPositiveHomeBoardOrBar() const;

    bool movePosChecker(int initialPos, int numPositions);
    bool moveNegChecker(int initialPos, int numPositions);

    bool isPosMoveLegal(int initialPos, int numPositions) const;
    bool isNegMoveLegal(int initialPos, int numPositions) const;

    bool allPosCheckersInInnerBoard() const;
    bool allNegCheckersInInnerBoard() const;

    bool posPlayerHasCheckersOnBar() const { return m_boardPos[BAR_POSITION] > 0; }
    bool negPlayerHasCheckersOnBar() const { return m_boardNeg[BAR_POSITION] > 0; } 

    int positivePipCount() const;
    int negativePipCount() const;

    friend struct std::hash<Board>;
    static const int BAR_POSITION;
    static const int ON_BOARD_POSITIONS;
     
  private:
    static int opposingPosition(int position) { return ON_BOARD_POSITIONS - 1 - position; };
    static int pipCount(const std::vector<int> &checkers);
    static bool allCheckersInInnerBoard(const std::vector<int> &checkers);
    static bool noCheckersHigherThan(const std::vector<int> &checkers, int position);
    static bool checkersInOppositeHomeBoardOrBar(const std::vector<int> &checkers);
    static bool isMoveLegal(
        int initialPos, 
        int numPositions, 
        const std::vector<int> &checkers, 
        const std::vector<int> &opponentCheckers);
    static void moveChecker(
        int initialPos,
        int numPositions,
        std::vector<int> &checkers, 
        std::vector<int> &opponentCheckers);
    void clearBoard();

  private:
    std::vector<int> m_boardPos;
    std::vector<int> m_boardNeg;
    static const int NUM_POSITIONS;
    int m_totalPosCheckers;
    int m_totalNegCheckers;
  };

}

#include "board.hxx"

#endif // BOARD_H__
