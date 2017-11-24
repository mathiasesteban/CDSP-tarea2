#include "../utils.h"
#include <iostream>
#include "../coder.h"

using namespace std;

void update_probabilities(PROBS* &probs,unsigned short int &scale, char c){


  probs[c-1].high++;

  for (unsigned short i = c ; i < 256  ; i++)
  {
    probs[i].low++;
    probs[i].high++;
  }
  scale++;


  if (scale == MAXIMUM_SCALE){
    probs = initialize_probabilities(256);
    scale = 256;
  }

  /*cout << "The following character \""
  		<< c << "\" updated its probability to "
  		<< probs[c-1].high - probs[c-1].low
  		<< "/" << scale << "\n";*/
}
