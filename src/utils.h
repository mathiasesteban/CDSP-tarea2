#ifndef _UTILS_H
#define _UTILS_H

#include <iostream>
#include "symbol.h"
#include <fstream>

using namespace std;

/*
* En este modulo se brindan tres operaciones fundamentales
* para manejar el modelo, inicializar, actualizar, y cambiar el estado
*/

// Inicializa el modelo probabilistico
PROBS** initialize_probabilities(int k, int M);

// Actualizar probabilidades
void update_probabilities(PROBS** &probs,unsigned int state,char c, unsigned int M);

// Cambiar el estado
void change_state(int &state,int k, char c);

// Escribe en el archivo la informacion actual
void imprimir_estadistica(string info_path, int state, unsigned int bytesLeidos, unsigned int bytesEscritos);

#endif