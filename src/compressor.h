#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include "symbol.h"

#include "coder.h"
#include "bitio.h"

#include <stdio.h>
#include <stdlib.h>

class compressor{
  public:
    void compress( void );
    void convert_int_to_symbol( char c, SYMBOL *s );
    void error_exit( char *message );
}; // End compressor class

#endif
