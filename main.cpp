/* Mathias Esteban - 4.957.703-8
 * Compresion de Datos Sin Perdida - FING Universidad de la Republica
 *
 * To build this program: makefile is provided, "make all" command used
 *
*/

#include "src/compressor.h"
#include "src/decompressor.h"

/*
 * This example program compresses an input string, sending
 * the output to a file.  It then expands the output file,
 * sending the decoded characters to the screen.
 */

int main()
{
    compressor* comp = new compressor();
    decompressor* decomp = new decompressor();

    comp->compress();
    decomp->decompress();

    delete(comp);
    delete(decomp);

    return 0;
}
