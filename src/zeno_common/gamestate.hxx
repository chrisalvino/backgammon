

namespace std {
template<> struct hash<zeno::GameState> {
  size_t operator()(const zeno::GameState &gameState) const {

    size_t retval = 0;
    retval += std::hash<zeno::Board>()(gameState.m_board);
    retval += 31 * retval + std::hash<unsigned int>()(gameState.m_dice[0]);
    retval += 31 * retval + std::hash<unsigned int>()(gameState.m_dice[1]);
    retval += 31 * retval + std::hash<int>()(gameState.m_cubeValue);
    retval += 31 * retval + std::hash<unsigned int>()(gameState.m_score[0]);
    retval += 31 * retval + std::hash<unsigned int>()(gameState.m_score[1]);
    retval += 31 * retval + std::hash<unsigned int>()(gameState.m_numGames);
    retval += 31 * retval + std::hash<double>()(gameState.m_meanScore);
    retval += 31 * retval + std::hash<double>()(gameState.m_squaredSumOfScoreMinusMean);
    retval += 31 * retval + std::hash<unsigned int>()(gameState.m_playerOnTurn);
    retval += 31 * retval + std::hash<unsigned int>()(gameState.m_cubeOwner);
    retval += 31 * retval + std::hash<int>()((int)gameState.m_gameType);
    retval += 31 * retval + std::hash<bool>()(gameState.m_currentlyDoubled);
    retval += 31 * retval + std::hash<bool>()(gameState.m_gameFinished);
    retval += 31 * retval + std::hash<bool>()(gameState.m_readyForRoll);
    
    return retval;
  }
};
}
