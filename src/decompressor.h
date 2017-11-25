#ifndef DECOMPRESSOR_H
#define DECOMPRESSOR_H

#include "symbol.h"
#include "bitio.h"
#include "coder.h"

#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

class decompressor{

  private:
    PROBS** probabilities;
    unsigned int state;
    unsigned int M;

  public:
  	decompressor(int k,int M);
    //void init_probabilities();
    void decompress(const char* file_path,const char* result_path );
    char convert_symbol_to_int( unsigned int count, SYMBOL *s );
    void error_exit( const char *message );
    ~decompressor();

};

#endif
