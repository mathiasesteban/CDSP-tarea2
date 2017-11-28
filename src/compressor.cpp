#include "compressor.h"
#include "utils.h"

// Rutina de error
void compressor::error_exit(const char *message )
{
    puts( message );
    exit( -1 );
}

compressor::compressor(int k, int M)
{
  //Comienzo en el estado 0
  state=0;
  this->M = M;
  this->k = k;
  probabilities = initialize_probabilities(k,M);
}

compressor::~compressor(){}

/*
 * This is the compress routine.  It shows the basic algorithm for
 * the compression programs used in this article.  First, an input
 * characters is loaded.  The modeling routines are called to
 * convert the character to a symbol, which has a high, low and
 * range.  Finally, the arithmetic coder module is called to
 * output the symbols to the bit stream.
 */

void compressor::compress(const char* file_path,const char* result_path)
{
    int i;
    char c;
    SYMBOL s;
    FILE *compressed_file;

    // Archivo a comprimir
    fstream source_file;
    source_file.open(file_path);

    // Archivo resultado de la compresion
    compressed_file=fopen( result_path, "wb" );

    if ( compressed_file == NULL )
        error_exit( "Could not open output file" );

    puts( "Compressing..." );

    initialize_output_bitstream();
    initialize_arithmetic_encoder();


    //Estadisticas
    unsigned int bytesLeidos = 0;
    unsigned int bytesEscritos = 0;
    unsigned int bitsAcumulados = 0;


    string info_path = string(result_path) +"_INFO";

    //fstream estadisticas;
    //estadisticas.open(info_path,std::fstream::out);

    std::ofstream estadisticas;
    estadisticas.open(info_path, std::ios_base::app);

    estadisticas << "Archivo de informacion sobre la compresion\n";
    estadisticas << "******************************************\n\n";
    estadisticas << "Archivo objetivo: " << file_path << "\n";
    estadisticas << "Orden de Markov: " << k << "\n";
    estadisticas << "Tamaño del alfabeto: " << M << "\n\n";
    estadisticas.close();

    /* ------------------------ PROCESO DE COMPRESION ----------------------*/
    for ( i=0 ; ; )
    {
        c = source_file.get();
        bytesLeidos++;

        convert_int_to_symbol( c, &s );

        encode_symbol( compressed_file, &s, bytesEscritos,bitsAcumulados );

        if (c == EOF){
          break;
        }

        update_probabilities(probabilities,state,c,M);
        change_state(state,k,c);

        // Por cada MB leido registro el estado actual
        if (bytesLeidos % 10485760 == 0){
          imprimir_estadistica(info_path,state,bytesLeidos,bytesEscritos);
        }

    }
    /* ----------------------------------------------------------------------*/

    flush_arithmetic_encoder( compressed_file );
    flush_output_bitstream( compressed_file );
    fclose( compressed_file);
}

/*
 * This routine is called to convert a character read in from
 * the text input stream to a low, high, range SYMBOL.  This is
 * part of the modeling function.  In this case, all that needs
 * to be done is to find the character in the probabilities table
 * and then retrieve the low and high values for that symbol.
 */
void compressor::convert_int_to_symbol( char c, SYMBOL *s )
{
    int i;

    i=0;
    for ( ; ; )
    {
        if ( c == probabilities[state][i].c )
        {
            s->low_count = probabilities[state][i].low;
            s->high_count = probabilities[state][i].high;
            s->scale = probabilities[state][M-1].high;
            return;
        }
        if ( (int)probabilities[state][i].c == -1 )
            error_exit( "Trying to encode a char not in the table" );
        i++;
    }
}
