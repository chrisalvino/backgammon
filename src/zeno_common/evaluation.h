
#ifndef EVALUATION_H__
#define EVALUATION_H__

namespace zeno {

	class Evaluation {

	public:
		Evaluation();

		~Evaluation();

		Evaluation(const Evaluation &rhs);

		Evaluation & operator=(const Evaluation &rhs);

	public:
		double getWinProbability() { return m_winProbability; }
		double getGammonProbability() { return m_winGammonProbability; }
		double getBackgammonProbability() { return m_winBackgammonProbability; }
		double getLoseGammonProbability() { return m_loseGammonProbability; }
		double getLoseBackgammonProbability() { return m_loseBackgammonProbability; }

		double getMoneyGameEquity(int gameStakes);

	private:
		double m_winProbability;
		double m_winGammonProbability;
		double m_winBackgammonProbability;
		double m_loseGammonProbability;
		double m_loseBackgammonProbability;
	};

}

#endif // EVALUATION_H__