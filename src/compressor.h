#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include "symbol.h"

#include "coder.h"
#include "bitio.h"

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

class compressor{
  private:
    PROBS** probabilities;
    int state;
    unsigned int M;
    unsigned int k;

  public:
  	compressor(int k,int M);
    void compress( const char* file_path,const char* result_path );
    void convert_int_to_symbol( char c, SYMBOL *s );
    void error_exit( const char *message );
    ~compressor();
}; // End compressor class

#endif
