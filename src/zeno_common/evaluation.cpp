

#include "evaluation.h"

using namespace zeno;

Evaluation::Evaluation() :
m_winProbability(0.0),
m_winGammonProbability(0.0),
m_winBackgammonProbability(0.0),
m_loseGammonProbability(0.0),
m_loseBackgammonProbability(0.0)
{

}

Evaluation::~Evaluation() {


}

double Evaluation::getMoneyGameEquity(int gameStakes) {
	return (
		m_winProbability 
		+ m_winGammonProbability
		+ m_winBackgammonProbability
		- (1.0 - m_winProbability)
		- m_loseGammonProbability
		- m_loseBackgammonProbability
		) * gameStakes;
}