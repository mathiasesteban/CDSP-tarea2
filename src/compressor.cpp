#include "compressor.h"

/*
 * A generic error routine.
 */
void compressor::error_exit( char *message )
{
    puts( message );
    exit( -1 );
}

compressor::compressor(){
  scale=0;
  probabilities = new PROBS[256];

}

compressor::~compressor(){

}

//PROBABILIDAD DE LETRAS a,b,c,d
/*
void compressor::init_probabilities(){
  probabilities[0] = {'a',0,1};
  probabilities[1] = {'b',1,2};
  probabilities[2] = {'c',2,3};
  probabilities[3] = {'d',3,4};
  probabilities[4] = {'\0',4,5};
  scale = 5; // Ojo con la escala!!!
}*/


void compressor::init_probabilities(){

  for (unsigned short i = 1 ; i < 256 ; i++)
  {
    int index = i-1;
    probabilities[index].c = i;
    probabilities[index].low = i-1;
    probabilities[index].high = i;
  }

  probabilities[255].c = '\0';
  probabilities[255].low = 255;
  probabilities[255].high = 256;

  scale = 256; // Ojo con la escala!!*

/*
  for (int i=0;i<256;i++){
    unsigned short c = probabilities[i].c;
    cout << i << " - " << "{" << c << ", " << probabilities[i].low << ", " <<  probabilities[i].high << "}\n";
  }*/

}


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


    // EN vez de tener un string hardcoded, leemos un archivo desde el fyle system
    fstream source_file;
    source_file.open(file_path);

    compressed_file=fopen( result_path, "wb" );

    if ( compressed_file == NULL )
        error_exit( "Could not open output file" );

    puts( "Compressing..." );

    initialize_output_bitstream();
    initialize_arithmetic_encoder();

    for ( i=0 ; ; )
    {
        c = source_file.get();
        // Como no es un string, sino que leo desde el stream, puedo en un cierto momento llegar a EOF,
        // esto es equivalente a llegar al char '\0' en el model anterior con string
        if (c == EOF){
          c = '\0';
        }
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
            s->scale = scale;
            return;
        }
        if ( probabilities[i].c == '\0' )
            error_exit( "Trying to encode a char not in the table" );
        i++;
    }
} // Notar que es importante que '\0' este al final de la tabla de probabilidades
