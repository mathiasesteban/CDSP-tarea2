#include "decompressor.h"
#include "utils.h"

// Rutina de error
void decompressor::error_exit( const char *message )
{
    puts( message );
    exit( -1 );
}

decompressor::decompressor(int k,int M){
  //Comienzo en el estado 0
  state=0;
  this->M = M;
  this->k = k;
  probabilities = initialize_probabilities(k,M);
}

decompressor::~decompressor(){}

/*
 * This expansion routine demonstrates the basic algorithm used for
 * decompression in this article.  It first goes to the modeling
 * module and gets the scale for the current context.  (Note that
 * the scale is fixed here, since this is not an adaptive model).
 * It then asks the arithmetic decoder to give a high and low
 * value for the current input number scaled to match the current
 * range.  Finally, it asks the modeling unit to convert the
 * high and low values to a symbol.
 */
void decompressor::decompress(const char* file_path,const char* result_path)
{
    FILE *compressed_file;
    SYMBOL s;
    char c;
    int count;

    // Archivo a decomprimir
    compressed_file=fopen( file_path, "rb" );

    // Resultado de la descompresion
    fstream result_file;
    result_file.open(result_path,std::fstream::out);

    if ( compressed_file == NULL )
        error_exit( "Could not open output file" );

    puts( "Decoding...\n" );

    initialize_input_bitstream();
    initialize_arithmetic_decoder( compressed_file );

    /* ---------- PROCESO DE DESCOMPRESION ------------- */
    for ( ; ; )
    {
        s.scale = probabilities[state][M-1].high;
        count = get_current_count( &s );

        c = convert_symbol_to_int( count, &s );

        remove_symbol_from_stream( compressed_file, &s );

        if ( c == EOF )
            break;

        update_probabilities(probabilities,state,c,M);
        change_state(state,k,c);

        result_file.put(c);
    }
    /* ----------------------------------------------------- */

    putc( '\n', stdout );
    result_file.close();
}

/*
 * This modeling function is called to convert a SYMBOL value
 * consisting of a low, high, and range value into a text character
 * that can be sent to a file.  It does this by finding the symbol
 * in the probability table that straddles the current range.
 */
char decompressor::convert_symbol_to_int( unsigned int count, SYMBOL *s )
{
    int i;
    i = 0;
    for ( ; ; )
    {
        if ( count >= probabilities[state][ i ].low &&
             count < probabilities[state][ i ].high )
        {
            s->low_count = probabilities[state][ i ].low;
            s->high_count = probabilities[state][ i ].high;
            s->scale = probabilities[state][M-1].high;

            //cout << "Decoded byte: " << probabilities[ i ].c << " (" << (int) probabilities[ i ].c << ")\n";

            return( probabilities[state][ i ].c );
        }
        if ( probabilities[state][ i ].c == '\0' )
            error_exit( "Failure to decode character" );
        i++;
    }
}
