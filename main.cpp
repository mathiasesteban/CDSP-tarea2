/* Mathias Esteban - 4.957.703-8
 * Compresion de Datos Sin Perdida - FING Universidad de la Republica
 *
 * To build this program: makefile is provided, "make all" command used
 *
*/

#include <string>

#include "src/compressor.h"
#include "src/decompressor.h"

using namespace std;

/*
 * This example program compresses an input string, sending
 * the output to a file.  It then expands the output file,
 * sending the decoded characters to the screen.
 */

int main()
{
    compressor* comp = new compressor();
    decompressor* decomp = new decompressor();

    string file_path = "file1";
    string compression_result_path = file_path + "_compressed";
    string decompression_result_path = file_path + "_decompressed";

    comp->compress(file_path.c_str(),compression_result_path.c_str());
    decomp->decompress(compression_result_path.c_str(),decompression_result_path.c_str());

    delete(comp);
    delete(decomp);

    return 0;
}
