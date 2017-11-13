#include "compressor.h"

/*
 * A generic error routine.
 */
void compressor::error_exit( char *message )
{
    puts( message );
    exit( -1 );
}

/*
 * This is the compress routine.  It shows the basic algorithm for
 * the compression programs used in this article.  First, an input
 * characters is loaded.  The modeling routines are called to
 * convert the character to a symbol, which has a high, low and
 * range.  Finally, the arithmetic coder module is called to
 * output the symbols to the bit stream.
 */

void compressor::compress()
{
    int i;
    char c;
    SYMBOL s;
    FILE *compressed_file;
    static char *input = "101";

    compressed_file=fopen( "test.cmp", "wb" );
    if ( compressed_file == NULL )
        error_exit( "Could not open output file" );
    puts( "Compressing..." );
    initialize_output_bitstream();
    initialize_arithmetic_encoder();
    for ( i=0 ; ; )
    {
        c = input[ i++ ];
        convert_int_to_symbol( c, &s );
        encode_symbol( compressed_file, &s );
        if ( c == '\0' )
            break;
    }
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
        if ( c == probabilities[ i ].c )
        {
            s->low_count = probabilities[ i ].low;
            s->high_count = probabilities[ i ].high;
            s->scale = 5;
            return;
        }
        if ( probabilities[i].c == '\0' )
            error_exit( "Trying to encode a char not in the table" );
        i++;
    }
}
