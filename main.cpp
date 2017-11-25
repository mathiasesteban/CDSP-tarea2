/* Mathias Esteban - 4.957.703-8
 * Compresion de Datos Sin Perdida - FING Universidad de la Republica
 *
*/



#include "src/compressor.h"
#include "src/decompressor.h"
#include <string>
#include <iostream>
using namespace std;

/*
 *
 */

int main(int argc, char **argv)
{
    bool continuar = true;

    while(continuar){
      system("clear");
      cout << "\n";
      cout << "******************************************\n";
      cout << "*     Compresion de Datos Sin Perdida    *\n";
      cout << "*     Tarea 2 - Codificacion Aritmetica  *\n";
      cout << "*     Mathias Esteban - 4957703          *\n";
      cout << "******************************************\n";
      cout << "\n";

      cout << "1) Comprimir un archivo.\n";
      cout << "2) Descomprimir un archivo.\n";
      cout << "3) Comprimir y Descomprimir un archivo.\n";
      cout << "4) Salir.\n";

      cout << "\nIngrese la opcion deseada: ";

      unsigned int opcion;

      cin >> opcion;

      if (opcion == 1){
        system("clear");
        cout << "Ingrese el path al archivo deseado: ";
        string path;
        cin >> path;
        cout << "Ingrese el orden de markov (k): ";
        int k;
        cin >> k;
        cout << "Ingrese el tamaño del alfabeto (M): ";
        int M;
        cin >> M;
        cout << "\n";

        string compression_result_path = path + "_C_K" + to_string(k) + "_M" + to_string(M);
        compressor* comp = new compressor(k,M);
        comp->compress(path.c_str(),compression_result_path.c_str());
        delete(comp);

        cout << "Finalizado correctamente. \n";
        cout << "Ingrese una tecla para continuar: ";
        string hold;
        cin >> hold;
      }
      else if(opcion == 2){

        system("clear");
        cout << "Ingrese el path al archivo deseado: ";
        string path;
        cin >> path;
        cout << "Ingrese el orden de markov (k): ";
        int k;
        cin >> k;
        cout << "Ingrese el tamaño del alfabeto (M): ";
        int M;
        cin >> M;
        cout << "\n";

        string decompression_result_path = path + "_D_K" + to_string(k) + "_M" + to_string(M);
        decompressor* decomp = new decompressor(k,M);
        decomp->decompress(path.c_str(),decompression_result_path.c_str());
        delete(decomp);

        cout << "Finalizado correctamente. \n";
        cout << "Ingrese una tecla para continuar: ";
        string hold;
        cin >> hold;

      }
      else if(opcion == 3){
        system("clear");
        cout << "Ingrese el path al archivo deseado: ";
        string path;
        cin >> path;
        cout << "Ingrese el orden de markov (k): ";
        int k;
        cin >> k;
        cout << "Ingrese el tamaño del alfabeto (M): ";
        int M;
        cin >> M;
        cout << "\n";

        string compression_result_path = path + "_C_K" + to_string(k) + "_M" + to_string(M);
        compressor* comp = new compressor(k,M);
        comp->compress(path.c_str(),compression_result_path.c_str());
        delete(comp);

        string decompression_result_path = path + "_D_K" + to_string(k) + "_M" + to_string(M);
        decompressor* decomp = new decompressor(k,M);
        decomp->decompress(compression_result_path.c_str(),decompression_result_path.c_str());
        delete(decomp);

        cout << "Finalizado correctamente. \n";
        cout << "Ingrese una tecla para continuar: ";
        string hold;
        cin >> hold;

      }
      else if (opcion == 4){
        continuar = false;
      }
      else{
        // No se reconoce la opcion ingresada
      }

    } // Fin while

    return 0;
}
