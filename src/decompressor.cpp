#include "decompressor.h"


/*
 * A generic error routine.
 */
void decompressor::error_exit( char *message )
{
    puts( message );
    exit( -1 );
}


/*
 * This method initialize de probability structure model to
 * compress the data
 *
 *
 */

// PROBABILITIES EXAMPLE
/*
void decompressor::init_probabilities(){
  probabilities[0] = {'a',0,1};
  probabilities[1] = {'b',1,2};
  probabilities[2] = {'c',2,3};
  probabilities[3] = {'d',3,4};
  probabilities[4] = {'\0',4,5};
  scale = 5; // Ojo con la escala!!!
}*/


void decompressor::init_probabilities(){

  for (int i = 1 ; i < 256 ; i++)
  {
    probabilities[i-1].c = i;
    probabilities[i-1].low = i-1;
    probabilities[i-1].high = i;
  }

  probabilities[255].c = '\0';
  probabilities[255].low = 255;
  probabilities[255].high = 256;

  scale = 256; // Ojo con la escala!!*

}


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

    compressed_file=fopen( file_path, "rb" );

    fstream result_file;
    result_file.open(result_path,std::fstream::out);

    if ( compressed_file == NULL )
        error_exit( "Could not open output file" );



    puts( "Decoding..." );
    printf( "Incoming characters: " );
    initialize_input_bitstream();
    initialize_arithmetic_decoder( compressed_file );

    for ( ; ; )
    {
        s.scale = scale;
        count = get_current_count( &s );
        c = convert_symbol_to_int( count, &s );
        if ( c == '\0' )
            break;
        remove_symbol_from_stream( compressed_file, &s );
        result_file.put(c);
    }
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
        if ( count >= probabilities[ i ].low &&
             count < probabilities[ i ].high )
        {
            s->low_count = probabilities[ i ].low;
            s->high_count = probabilities[ i ].high;
            s->scale = scale;
            return( probabilities[ i ].c );
        }
        if ( probabilities[ i ].c == '\0' )
            error_exit( "Failure to decode character" );
        i++;
    }
}
