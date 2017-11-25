#ifndef _UTILS_H
#define _UTILS_H

#include <iostream>
#include "symbol.h"

using namespace std;

PROBS** initialize_probabilities(int k, int M);
void update_probabilities(PROBS** &probs,unsigned int state,char c, unsigned int M);

#endif