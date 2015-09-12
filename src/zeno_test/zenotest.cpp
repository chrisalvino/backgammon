
#include <cstdlib>
#include <iostream>
#include "gamestate.h"
#include "checkertests.h"

using namespace zeno;

int main(int argc, char **argv) {

	try {
		switch(atoi(argv[1])) {
			case 1:
				if (!comeOffFromBarTest()) {
					return 1;
				}
			break;
			default:
				return 1;
		}


	} catch (const std::exception &e) {
		return 1;
	}

	return 0;
}