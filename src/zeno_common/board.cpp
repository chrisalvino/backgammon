
#include "board.h"

#include <vector>
#include "exceptions.h"

using namespace zeno;

const int Board::NUM_POSITIONS=25;  // 25 positions, 0 to 23 are on the board, 24 is bar

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

void Board::clearBoard() {
  for(int i=0;i<NUM_POSITIONS;++i) {
    m_boardPos[i] = 0;
    m_boardNeg[i] = 0;
  }
}

int Board::getNumPositiveCheckersOnBoardOrBar() const {
  int posOnBoardOrBar = 0;
  for(int i=0;i<NUM_POSITIONS;++i) {
    posOnBoardOrBar += m_boardPos[i];
  }
  return posOnBoardOrBar;
}

int Board::getNumNegativeCheckersOnBoardOrBar() const {
  int negOnBoardOrBar = 0;
  for(int i=0;i<NUM_POSITIONS;++i) {
    negOnBoardOrBar += m_boardNeg[i];
  }
  return negOnBoardOrBar;
}

int Board::getNumPositiveCheckersBornOff() const {
  return m_totalPosCheckers - getNumPositiveCheckersOnBoardOrBar();
}

int Board::getNumNegativeCheckersBornOff() const {
  return m_totalNegCheckers - getNumNegativeCheckersOnBoardOrBar();
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
  m_totalPosCheckers = 15;

  // the negative player moves downward too, from 23 down to 0 and then off
  // this means that position X for the positive player is the same as position
  // 25-X for the negative player
  m_boardNeg[21] = 1;
  m_boardNeg[22] = 1;
  m_boardNeg[23] = 1;
  m_totalNegCheckers = 15;
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

bool Board::moveChecker(int initialPos, bool positivePlayer, int numPositions) {
  if (!isMoveLegal(initialPos, positivePlayer, numPositions) ) {
    throw zeno::IllegalMoveException();
  }

  return true;
}

bool Board::isMoveLegal(int initialPos, bool positivePlayer,  int numPositions) {

  return true;
}
