#include "../utils.h"
#include <iostream>
#include "../coder.h"

using namespace std;

/*
* La siguiente funcion, es la encargada de actualizar el modelo probabilistico
* Para esto,dado el estado actual,aumenta el ancho de intervalo del char leido.
* Debido a las limitaciones del codificador y de la manipulacion de memoria
* finita, se debe considerar la posibilidad de overflow y evitarla. Ante esto
* se realiza un reescalado de los intervalos en el estado considerado, el mismo
* consiste en dividir los totales entre 2.
*/


void update_probabilities(PROBS** &probs,unsigned int state,char c, unsigned int M){

  // Se aumenta la probababilidad del char c
  probs[state][c-1].high++;
  // Se aumentan en uno todos los intervalos superiores a c
  for (unsigned short i = c ; i < M  ; i++)
  {
    probs[state][i].low++;
    probs[state][i].high++;
  }

  /* La representacion utilizada puede ocasionar overflow, se debe reescalar
   ************************************************************************ */

  /* Reescalado a 0: reinicializa la estructura
  este metodo desperdicia informacion ya recopilada
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

  } // Fin reescalado
} // Fin actualizacion de probabilidades
