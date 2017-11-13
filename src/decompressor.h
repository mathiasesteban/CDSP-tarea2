#ifndef DECOMPRESSOR_H
#define DECOMPRESSOR_H

#include "symbol.h"
#include "bitio.h"
#include "coder.h"


#include <stdlib.h>
#include <stdio.h>

class decompressor{

  public:
    void decompress( void );
    char convert_symbol_to_int( unsigned int count, SYMBOL *s );
    void error_exit( char *message );

};

#endif
