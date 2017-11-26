#include "../utils.h"
#include <iostream>

using namespace std;

/*
* Funcion encargada de inicializar el modelo estadistico
* Para cada uno de los estados (la cantidad queda determinada por el orden de
* markov k) se inicializa un array con los intervalos de cada char.
* En la ultima posicion de dicho array se mapea el simbolo '\0'
*/

PROBS** initialize_probabilities(int k, int M){

  cout << "Initializing Probabilities\n";

  PROBS** model;
  unsigned int tope;

  if (k == 0){
    model = new PROBS*[1];
    tope = 1;
  }
  else if (k == 1){
    model = new PROBS*[256];
    tope = 256;
  }
  else{
    model = new PROBS*[65536];
    tope = 65536;
  }

  /* Se inicializa cada simbolo con una probabilidad de 1/256
  independientemente del orden markov (k) elegido
  *************************************************************/

  for(int j = 0; j<tope; j++){
    PROBS* probabilities = new PROBS[M];
    for (unsigned short i = 1 ; i < M ; i++)
    {
      int index = i-1;
      probabilities[index].c = i;
      probabilities[index].low = i-1;
      probabilities[index].high = i;
    }

    probabilities[M-1].c = -1;
    probabilities[M-1].low = M -1 ;
    probabilities[M-1].high = M;

    model[j] = probabilities;
  }

  return model;

} // Fin inicializacion

/* Ejemplo con alfabeto A = { a,b,c,d }
*******************************************************/
/*
void compressor::init_probabilities(){
  probabilities[0] = {'a',0,1};
  probabilities[1] = {'b',1,2};
  probabilities[2] = {'c',2,3};
  probabilities[3] = {'d',3,4};
  probabilities[4] = {'\0',4,5};
  scale = 5;
}*/