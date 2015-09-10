
#include "board.h"

#include <vector>
#include <unordered_set>
#include "exceptions.h"

using namespace zeno;

const int Board::NUM_POSITIONS=25;  // 25 positions, 0 to 23 are on the board
const int Board::ON_BOARD_POSITIONS=24;
const int Board::BAR_POSITION=24;   // 24 is bar

Board::Board(GameType gameType) {
  m_boardPos.resize(NUM_POSITIONS); 
  m_boardNeg.resize(NUM_POSITIONS); 

  switch (gameType) {
    case BACKGAMMON:
    this->setUpBackgammonCheckers();
    break;
    case NACKGAMMON:
    this->setUpNackgammonCheckers();
    break;
    case HYPERGAMMON:
    this->setUpHypergammonCheckers();
    break;      
  }
}

Board::~Board() {

}

bool Board::operator==(const Board &rhs) const {
  return 
  m_boardPos == rhs.m_boardPos &&
  m_boardNeg == rhs.m_boardNeg &&
  m_totalPosCheckers == rhs.m_totalPosCheckers &&
  m_totalNegCheckers == rhs.m_totalNegCheckers;
}

void Board::clearBoard() {
  for (int i=0;i<NUM_POSITIONS;++i) {
    m_boardPos[i] = 0;
    m_boardNeg[i] = 0;
  }
}


bool Board::positiveCheckersInNegativeHomeBoardOrBar() const {
  return checkersInOppositeHomeBoardOrBar(m_boardPos);
}

bool Board::negativeCheckersInPositiveHomeBoardOrBar() const { 
  return checkersInOppositeHomeBoardOrBar(m_boardNeg);
}

bool Board::checkersInOppositeHomeBoardOrBar(const std::vector<int> &checkers) {
  for (int i=18;i<NUM_POSITIONS;++i) {
    if (checkers[i] > 0) return true;
  }
  return false;
}

int Board::numPositiveCheckersOnBoardOrBar() const {
  int posOnBoardOrBar = 0;
  for(int i=0;i<NUM_POSITIONS;++i) {
    posOnBoardOrBar += m_boardPos[i];
  }
  return posOnBoardOrBar;
}

int Board::numNegativeCheckersOnBoardOrBar() const {
  int negOnBoardOrBar = 0;
  for(int i=0;i<NUM_POSITIONS;++i) {
    negOnBoardOrBar += m_boardNeg[i];
  }
  return negOnBoardOrBar;
}

int Board::numPositiveCheckersBornOff() const {
  return m_totalPosCheckers - numPositiveCheckersOnBoardOrBar();
}

int Board::numNegativeCheckersBornOff() const {
  return m_totalNegCheckers - numNegativeCheckersOnBoardOrBar();
}

int Board::pipCount(const std::vector<int> &checkers) {
  int pipCount = 0;
  for(int i=0;i<Board::NUM_POSITIONS;++i) {
    pipCount += checkers[i] * (i+1);
  }
  return pipCount;
}

int Board::positivePipCount() const {
  return pipCount(m_boardPos);
}

int Board::negativePipCount() const {
  return pipCount(m_boardNeg);
}

void Board::setUpBackgammonCheckers() {
  clearBoard();

  // the positive player moves downward, from 23 down to 0 and off
  m_boardPos[5] = 5;
  m_boardPos[7] = 3;
  m_boardPos[12] = 5;
  m_boardPos[23] = 2;
  m_totalPosCheckers = 15;

  // the negative player moves downward too, from 23 down to 0 and then off
  // this means that position X for the positive player is the same as position
  // 25-X for the negative player
  m_boardNeg[5] = 5;
  m_boardNeg[7] = 3;
  m_boardNeg[12] = 5;
  m_boardNeg[23] = 2;
  m_totalNegCheckers = 15;
}

void Board::setUpNackgammonCheckers() {
  clearBoard();

  // the positive player moves downward, from 23 down to 0 and off
  m_boardPos[5] = 4;
  m_boardPos[7] = 3;
  m_boardPos[12] = 4;
  m_boardPos[22] = 2;
  m_boardPos[23] = 2;
  m_totalPosCheckers = 15;

  // the negative player moves downward too, from 23 down to 0 and then off
  // this means that position X for the positive player is the same as position
  // 25-X for the negative player
  m_boardNeg[5] = 4;
  m_boardNeg[7] = 3;
  m_boardNeg[12] = 4;
  m_boardNeg[22] = 2;
  m_boardNeg[23] = 2;
  m_totalNegCheckers = 15;
}

void Board::setUpHypergammonCheckers() {
  clearBoard();

  // the positive player moves downward, from 23 down to 0 and off
  m_boardPos[21] = 1;
  m_boardPos[22] = 1;
  m_boardPos[23] = 1;
  m_totalPosCheckers = 3;

  // the negative player moves downward too, from 23 down to 0 and then off
  // this means that position X for the positive player is the same as position
  // 25-X for the negative player
  m_boardNeg[21] = 1;
  m_boardNeg[22] = 1;
  m_boardNeg[23] = 1;
  m_totalNegCheckers = 3;
}

Board::Board(const Board &rhs) :
m_boardPos(rhs.m_boardPos),
m_boardNeg(rhs.m_boardNeg),
m_totalPosCheckers(rhs.m_totalPosCheckers),
m_totalNegCheckers(rhs.m_totalNegCheckers) {

}

Board & Board::operator=(const Board &rhs) {
  if (this == &rhs) {
    return *this;
  }

  this->m_boardPos = rhs.m_boardPos;
  this->m_boardNeg = rhs.m_boardNeg;
  this->m_totalPosCheckers = rhs.m_totalPosCheckers;
  this->m_totalNegCheckers = rhs.m_totalNegCheckers;

  return *this;
}

bool Board::movePosChecker(int initialPos, int numPositions) {
  if (isPosMoveLegal(initialPos, numPositions)) {
    // move it and return 
    moveChecker(initialPos, numPositions, m_boardPos, m_boardNeg);
    return true;
  }
  return false;
}

bool Board::moveNegChecker(int initialPos, int numPositions) {
  if (isNegMoveLegal(initialPos, numPositions)) {
    // move it and return 
    moveChecker(initialPos, numPositions, m_boardNeg, m_boardPos);
    return true;
  }
  return false;
}

void Board::moveChecker(
  int initialPos,
  int numPositions,
  std::vector<int> &checkers, 
  std::vector<int> &opponentCheckers) {
  checkers[initialPos] -= 1; // take checker off initial position

  // now determine target position
  int targetPos = initialPos - numPositions;
  int opponentTargetPos = opposingPosition(targetPos);

  // only care about greater than 0 case
  // if less than or equal to 0, it's borne off
  if (targetPos >= 0) { 
    checkers[targetPos] += 1; 

    if (opponentCheckers[opponentTargetPos] >= 2) {
      throw IllegalMoveException();
    }

      // remove opponent checker from that position
      // and place on opponents bar
    if (opponentCheckers[opponentTargetPos] == 1) {
      opponentCheckers[opponentTargetPos] = 0;  
      opponentCheckers[BAR_POSITION] += 1;
    }
  }
}

bool Board::isPosMoveLegal(int initialPos, int numPositions) const {
  return isMoveLegal(initialPos, numPositions, m_boardPos, m_boardNeg);
}

bool Board::isNegMoveLegal(int initialPos, int numPositions) const {
  return isMoveLegal(initialPos, numPositions, m_boardNeg, m_boardPos);
}

bool Board::isMoveLegal(
  int initialPosition, 
  int numPositions, 
  const std::vector<int> &checkers, 
  const std::vector<int> &opponentCheckers) {

  if (initialPosition < 0) {
    return false;
  }

  if (initialPosition > BAR_POSITION) {
    return false;
  }

  if (numPositions < 1 || numPositions > 6) {
    return false;
  }

  // if you have someone on the bar, must move it first
  // if you don't, then move is illegal
  if (checkers[BAR_POSITION] > 0) {
    if (initialPosition != BAR_POSITION) {
      return false;
    }
  }

  // if player has no checkers on that position, then must be illegal
  if (checkers[initialPosition] == 0) {
    return false;
  }

  int targetPosition = initialPosition - numPositions;
  
  // bearing off case next
  if (targetPosition < 0) {
    // no checkers outside of inner board  
    if (!allCheckersInInnerBoard(checkers)) {
      return false;
    }
    // if exact roll then ok
    if (targetPosition == -1) {
      return true;
    } else {
      // must be highest position
      if(!noCheckersHigherThan(checkers, initialPosition)) {
        return false;
      }
    }
    return true;
  }
  
  // otherwise targetPosition >= 0 so we can check opposing position 
  // for blocked point
  int opponentTargetPosition = opposingPosition(targetPosition);

  // can't possibly move somewhere if oppponent has two or more checkers on it
  // we don't have to check for 
  if (opponentCheckers[opponentTargetPosition] >= 2) {
    return false;
  }

  return true;
}

bool Board::allPosCheckersInInnerBoard() const {
  return allCheckersInInnerBoard(m_boardPos);
}
bool Board::allNegCheckersInInnerBoard() const {
  return allCheckersInInnerBoard(m_boardNeg);
}

bool Board::noCheckersHigherThan(const std::vector<int> &checkers, int position) {
  for (int i=position+1;i<NUM_POSITIONS;++i) {
    if (checkers[i] > 0) {
      return false;
    }
  }
  return true;
}

bool Board::allCheckersInInnerBoard(const std::vector<int> &checkers) {
  return noCheckersHigherThan(checkers, 5);
}
