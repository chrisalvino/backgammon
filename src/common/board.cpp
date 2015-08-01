
#include "board.h"

#include <vector>
#include "exceptions.h"

const int Board::NUM_POSITIONS=24;

Board::Board() :
  m_numPositiveOnBar(0),
  m_numNegativeOnBar(0),
  m_numPositiveBornOff(0),
  m_numNegativeBornOff(0)
{
  m_board.resize(NUM_POSITIONS); 
  for(int i=0;i<NUM_POSITIONS;++i) {
    m_board[i] = 0;
  }
}

Board::~Board() {

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
    throw bg::IllegalMoveException();
  }
}

bool Board::isMoveLegal(int initialPos, bool positivePlayer,  int numPositions) {

}
