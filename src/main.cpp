

#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "zeno_common/defaultdie.h"
#include "zeno_common/gamestate.h"
#include "display/terminaldisplay.h"
#include <iostream>

#include <vector>

using namespace zeno;

int main() {
	srand48 (time (0));
	DefaultDie die;

	GameState gameState;
	gameState.initializeBackgammon();

	

	TerminalDisplay terminalDisplay;

	terminalDisplay.showBoard(gameState, std::cout);


	// std::vector<int> tally;
	// tally.resize(7);
	// for (int i=0;i<7;i++) {
	// 	tally[i] = 0;
	// }
// 
	// for (int i=0;i<100000000;i++) {
	// 	tally[die.getDieRoll()]++;
	// }
// 
	// std::cout << tally[0] << std::endl;
	// std::cout << tally[1] << std::endl;
	// std::cout << tally[2] << std::endl;
	// std::cout << tally[3] << std::endl;
	// std::cout << tally[4] << std::endl;
	// std::cout << tally[5] << std::endl;
	// std::cout << tally[6] << std::endl;
}