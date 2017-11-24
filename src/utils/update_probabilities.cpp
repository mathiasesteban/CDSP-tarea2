#include "../utils.h"
#include <iostream>
#include "../coder.h"

using namespace std;

void update_probabilities(PROBS* &probs,unsigned short int &scale, char c){

  // Se aumenta la probababilidad del char c
  probs[c-1].high++;
  for (unsigned short i = c ; i < 256  ; i++)
  {
    probs[i].low++;
    probs[i].high++;
  }
  scale++;

  /* La representacion utilizada puede ocasionar overflow, se debe reescalar
   ************************************************************************ */

  /* Reescalado a 0: reinicializa la estructura
  *********************************************** */
  /*
  if (scale == MAXIMUM_SCALE){
    probs = initialize_probabilities(256);
    scale = 256;
  }
  */

  /* Reescalado a dos: reescala todas los intervalos entre 2
  ********************************************************** */
  if (scale == MAXIMUM_SCALE){

    probs[0].low = probs[0].low / 2 ;
    probs[0].high = probs[0].high / 2;

    if (probs[0].high == 0)
      probs[0].high = 1;

    for (unsigned short i = 1 ; i < 256  ; i++)
    {
      probs[i].low = probs[i-1].high;
      probs[i].high = probs[i].high / 2;

      if(probs[i].high <= probs[i].low)
        probs[i].high = probs[i].low +1 ;
    }
    scale = probs[255].high;

  }
}
