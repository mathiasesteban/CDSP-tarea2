#include "../utils.h"


void imprimir_estadistica(string info_path, int state, unsigned int bytesLeidos, unsigned int bytesEscritos){

  char char1 = (state & 65280) >> 8;
  char char2 = state & 127;

  string string1;
  if (char1 == '\0')
    string1 = "";
  else
    string1.push_back(char1);


  string string2;
  if (char2 == '\0')
    string2 = "";
  else
    string2.push_back(char2);

  //fstream estadisticas;
  //estadisticas.open(info_path,std::fstream::out);

  std::ofstream estadisticas;
  estadisticas.open(info_path, std::ios_base::app);

  estadisticas << "Estado: " << state << "(" << string1 << string2 << ") | "
               << "Bytes leidos: " << bytesLeidos << " | "
               << "Bytes escritos: " << bytesEscritos << " | "
               << "Tasa de compresion: "  <<  ((bytesLeidos - bytesEscritos)*100 / bytesLeidos) << "%\n";

  estadisticas.close();
}


