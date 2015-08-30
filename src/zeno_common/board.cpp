
#include "board.h"

#include <vector>
#include "exceptions.h"

using namespace zeno;

const int Board::NUM_POSITIONS=25;  // 25 positions, 0 to 23 are on the board, 24 is bar

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
}

Board::Board(const Board &rhs) :
  m_board(rhs.m_board)
{
  
}

Board & Board::operator=(const Board &rhs) {
  if (this == &rhs) {
    return *this;
  }

  this->m_board = rhs.m_board;

  return *this;
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
