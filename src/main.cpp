

#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "zeno_common/defaultdie.h"
#include "zeno_common/randomplayer.h"
#include "zeno_common/hittingrandomplayer.h"
#include "display/terminaldisplay.h"
#include "game.h"
#include <iostream>

#include <vector>

using namespace zeno;

int main() {
	//srand48 (time (0));
	srand48 (12345);
	DefaultDie die;

	Game game;

	TerminalDisplay display(std::cout);
	HittingRandomPlayer posPlayer;
	RandomPlayer negPlayer;

	//game.setDisplay(&display);
	game.setDie(&die);
	game.setPlayerPos(&posPlayer);
	game.setPlayerNeg(&negPlayer);
	//game.play();

	
	for (int i=1;i<1000;++i) {
		game.play();
		if (i % 100 == 0) {
			std::cout << "Pos: " << game.score()[0] << " Neg: " << game.score()[1] << " ppg: " << 
			game.pointsPerGame() << " ±" << game.standardError() << std::endl;
		}
	}

	// std::cout << tally[0] << std::endl;
	// std::cout << tally[1] << std::endl;
	// std::cout << tally[2] << std::endl;
	// std::cout << tally[3] << std::endl;
	// std::cout << tally[4] << std::endl;
	// std::cout << tally[5] << std::endl;
	// std::cout << tally[6] << std::endl;
}