
#include "defaultdie.h"
#include <stdlib.h>
#include <math.h>

using namespace zeno;

DefaultDie::DefaultDie() {

}

DefaultDie::~DefaultDie() {

}

int DefaultDie::getDieRoll() {
//	return ceil(static_cast<double>(rand()) / RAND_MAX * 6.0);	
	return ceil(drand48() * 6.0);
}