
namespace std {
template<> struct hash<zeno::Board> {
  size_t operator()(const zeno::Board &board) const {

    size_t retval = 0;
    retval += std::hash<int>()(board.m_totalPosCheckers);
    retval += 31 * retval + std::hash<int>()(board.m_totalNegCheckers);

    auto iteEnd = board.m_boardPos.end();
    for (auto ite = board.m_boardPos.begin();ite != iteEnd;++ite) {
      retval += 31 * retval + std::hash<int>()(*ite);
    }

    iteEnd = board.m_boardNeg.end();
    for (auto ite = board.m_boardNeg.begin();ite != iteEnd;++ite) {
      retval += 31 * retval + std::hash<int>()(*ite);
    }    

    return retval;
  }
};
}