#include "../utils.h"
#include <iostream>

using namespace std;

void update_probabilities(PROBS* &probs,unsigned short int &scale, char c){


  probs[c-1].high++;

  for (unsigned short i = c ; i < scale -1  ; i++)
  {
    probs[i].low++;
    probs[i].high++;
  }
  scale++;

  cout << "The following character \"" 
  		<< c << "\" updated its probability to " 
  		<< probs[c-1].high - probs[c-1].low 
  		<< "/" << scale << "\n";
}
