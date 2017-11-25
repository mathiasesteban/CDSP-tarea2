#include "../utils.h"
#include <iostream>
#include "../coder.h"

using namespace std;

void update_probabilities(PROBS** &probs,unsigned int state,char c, unsigned int M){

  // Se aumenta la probababilidad del char c
  probs[state][c-1].high++;
  for (unsigned short i = c ; i < M  ; i++)
  {
    probs[state][i].low++;
    probs[state][i].high++;
  }

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
  se pierde menos informacion que con el metodo anterior
  ********************************************************** */
  if (probs[state][M-1].high == MAXIMUM_SCALE){

    probs[state][0].low = probs[state][0].low / 2 ;
    probs[state][0].high = probs[state][0].high / 2;

    if (probs[state][0].high == 0)
      probs[state][0].high = 1;

    for (unsigned short i = 1 ; i < M  ; i++)
    {
      probs[state][i].low = probs[state][i-1].high;
      probs[state][i].high = probs[state][i].high / 2;

      if(probs[state][i].high <= probs[state][i].low)
        probs[state][i].high = probs[state][i].low +1 ;
    }

  }
}
