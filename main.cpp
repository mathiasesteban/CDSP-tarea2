/* Mathias Esteban - 4.957.703-8
 * Compresion de Datos Sin Perdida - FING Universidad de la Republica
 *
*/

#include <string>

#include "src/compressor.h"
#include "src/decompressor.h"

using namespace std;

/*
 *
 */

int main(int argc, char **argv)
{

    string file_path = argv[1];
    string compression_result_path = file_path + "_compressed";
    string decompression_result_path = file_path + "_decompressed";

    system("clear");
    cout << "\n";
    cout << "******************************************\n";
    cout << "*     Compresion de Datos Sin Perdida    *\n";
    cout << "*     Tarea 2 - Codificacion Aritmetica  *\n";
    cout << "*     Mathias Esteban - 4957703          *\n";
    cout << "******************************************\n";
    cout << "\n";

    int k = atoi(argv[2]);
    int M = atoi(argv[3]);

    cout << "Se procedera con los siguientes parametros:\n";
    cout << "Archivo: " << argv[1] << "\n";
    cout << "K = " << k << "\n";
    cout << "M = " << M << "\n\n";

    compressor* comp = new compressor(k,M);
    comp->compress(file_path.c_str(),compression_result_path.c_str());

    decompressor* decomp = new decompressor(k,M);
    decomp->decompress(compression_result_path.c_str(),decompression_result_path.c_str());

    cout << "Finalizado Correctamente.\n\n";

    return 0;
}
