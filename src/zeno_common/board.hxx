
namespace std {
template<> struct hash<zeno::Board> {
  size_t operator()(const zeno::Board &board) const {

    size_t retval = 0;
    retval += std::hash<int>()(board.m_totalPosCheckers);
    retval += 31 * retval + std::hash<int>()(board.m_totalNegCheckers);

    for (int i=0;i<zeno::Board::NUM_POSITIONS;++i) {
      retval += 31 * retval + std::hash<int>()(board.m_boardPos[i]);
      retval += 31 * retval + std::hash<int>()(board.m_boardNeg[i]);
    }

    return retval;
  }
};
}