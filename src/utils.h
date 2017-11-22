#ifndef _UTILS_H
#define _UTILS_H

#include <iostream>
#include "symbol.h"

using namespace std;

PROBS* initialize_probabilities(unsigned int dimension);
void update_probabilities(PROBS* &probs,unsigned short int &scale,char c);

#endif