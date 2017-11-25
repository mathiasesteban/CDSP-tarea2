#include "../utils.h"

void change_state(int &state,int k, char c){

  /*
  * En cada nueva lectura se debe actualizar el estado en la cadena de
  * markov. Los casos k = 0 y k = 1 son triviales.
  * Para k = 2, el metodo consiste en lo siguiente:
  *
  * 1- Shiftear el estado actual (state) 8 bits a hacia la izquierda
  *
  * 2- Asegurar que exista un 0 en los bits no deseados, para esto realizar
  *    un and bit a bit con la mascara '65280'
  *
  * 3- Agregar la informacion del nuevo char leido, mediante un or bit a bit
  *
  */

  if (k == 0){
    // Estado unico, no hacer nada
  }
  else if (k==1){
    // Con k = 1, tenemos M estados
    state = (unsigned char) c;
  }
  else{
    // Con k=2, 65536 estados
    k = k << 8;
    k = k &  65280;
    k = k | c;
  }

} // Fin change_state