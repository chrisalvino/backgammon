
#include "board.h"

#include <vector>
#include "exceptions.h"

using namespace zeno;

const int Board::NUM_POSITIONS=25;  // 25 positions, 0 to 23 are on the board, 24 is bar

Board::Board() {
  m_boardPos.resize(NUM_POSITIONS); 
  m_boardNeg.resize(NUM_POSITIONS); 

  this->reset();
}

Board::~Board() {

}

void Board::reset() {
  for(int i=0;i<NUM_POSITIONS;++i) {
    m_boardPos[i] = 0;
    m_boardNeg[i] = 0;
  }

  // the positive player moves downward, from 23 down to 0 and off
  m_boardPos[5] = 5;
  m_boardPos[7] = 3;
  m_boardPos[12] = 5;
  m_boardPos[23] = 2;

  // the negative player moves downward too, from 23 down to 0 and then off
  // this means that position X for the positive player is the same as position
  // 25-X for the negative player
  m_boardNeg[5] = 5;
  m_boardNeg[7] = 3;
  m_boardNeg[12] = 5;
  m_boardNeg[23] = 2;
}

Board::Board(const Board &rhs) :
  m_boardPos(rhs.m_boardPos),
  m_boardNeg(rhs.m_boardNeg) {
  
}

Board & Board::operator=(const Board &rhs) {
  if (this == &rhs) {
    return *this;
  }

  this->m_boardPos = rhs.m_boardPos;
  this->m_boardNeg = rhs.m_boardNeg;

  return *this;
}

bool Board::moveChecker(int initialPos, bool positivePlayer, int numPositions) {
  if (!isMoveLegal(initialPos, positivePlayer, numPositions) ) {
    throw zeno::IllegalMoveException();
  }

  return true;
}

bool Board::isMoveLegal(int initialPos, bool positivePlayer,  int numPositions) {

  return true;
}
