#include "../utils.h"
#include <iostream>

using namespace std;

PROBS* initialize_probabilities(unsigned int dimension){

PROBS* probabilities = new PROBS[dimension];

  for (unsigned short i = 1 ; i < dimension ; i++)
  {
    int index = i-1;
    probabilities[index].c = i;
    probabilities[index].low = i-1;
    probabilities[index].high = i;
  }

  probabilities[dimension -1 ].c = '\0';
  probabilities[dimension -1 ].low = dimension -1 ;
  probabilities[dimension -1 ].high = dimension;

  /*for (int i=0;i<256;i++){
    unsigned short c = probabilities[i].c;
    cout << i << " - " << "{" << c << ", " << probabilities[i].low << ", " <<  probabilities[i].high << "}\n";
  }*/

return probabilities;

}


//PROBABILIDAD DE LETRAS a,b,c,d
/*
void compressor::init_probabilities(){
  probabilities[0] = {'a',0,1};
  probabilities[1] = {'b',1,2};
  probabilities[2] = {'c',2,3};
  probabilities[3] = {'d',3,4};
  probabilities[4] = {'\0',4,5};
  scale = 5; // Ojo con la escala!!!
}*/