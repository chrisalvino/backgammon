
#include "defaultdie.h"
#include <stdlib.h>
#include <math.h>

using namespace zeno;

DefaultDie::DefaultDie() {

}

DefaultDie::~DefaultDie() {

}

int DefaultDie::getDieRoll() {
	return ceil(drand48() * 6.0);
}