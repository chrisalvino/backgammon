
#include "board.h"

#include <vector>
#include "exceptions.h"

using namespace zeno;

const int Board::NUM_POSITIONS=24;

Board::Board() {
  m_board.resize(NUM_POSITIONS); 
  for(int i=0;i<NUM_POSITIONS;++i) {
    m_board[i] = 0;
  }

  this->reset();
}

Board::~Board() {

}

void Board::reset() {
  m_board[0] = -2;
  m_board[5] = 5;
  m_board[7] = 3;
  m_board[11] = -5;
  m_board[12] = 5;
  m_board[16] = -3;
  m_board[18] = -5;
  m_board[23] = 2;
  m_numPositiveOnBar = 0;
  m_numNegativeOnBar = 0;
  m_numPositiveBornOff = 0;
  m_numNegativeBornOff = 0;
}

Board::Board(const Board &rhs) :
  m_board(rhs.m_board),
  m_numPositiveOnBar(rhs.m_numPositiveOnBar),
  m_numNegativeOnBar(rhs.m_numNegativeOnBar),
  m_numPositiveBornOff(rhs.m_numPositiveBornOff),
  m_numNegativeBornOff(rhs.m_numNegativeBornOff)
{
  
}

int Board::getPosition(int pos) {
  return m_board[pos];
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
