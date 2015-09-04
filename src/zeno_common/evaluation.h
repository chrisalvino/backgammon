
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
		double winProbability() { return m_winProbability; }
		double gammonProbability() { return m_winGammonProbability; }
		double backgammonProbability() { return m_winBackgammonProbability; }
		double loseGammonProbability() { return m_loseGammonProbability; }
		double loseBackgammonProbability() { return m_loseBackgammonProbability; }

		double moneyGameEquity(int gameStakes);

	private:
		double m_winProbability;
		double m_winGammonProbability;
		double m_winBackgammonProbability;
		double m_loseGammonProbability;
		double m_loseBackgammonProbability;
	};

}

#endif // EVALUATION_H__