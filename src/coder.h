/*
 * Listing 1 -- coder.h
 *
 * This header file contains the constants, declarations, and
 * prototypes needed to use the arithmetic coding routines.  These
 * declarations are for routines that need to interface with the
 * arithmetic coding stuff in coder.c
 *
 */

#include <stdio.h>
#include "symbol.h"

#define MAXIMUM_SCALE   16383  /* Maximum allowed frequency count */
#define ESCAPE          256    /* The escape symbol               */
#define DONE            -1     /* The output stream empty  symbol */
#define FLUSH           -2     /* The symbol to flush the model   */

extern long underflow_bits;    /* The present underflow count in  */
                               /* the arithmetic coder.           */
/*
 * Function prototypes.
 */
void initialize_arithmetic_decoder( FILE *stream );
void remove_symbol_from_stream( FILE *stream, SYMBOL *s );
void initialize_arithmetic_encoder( void );
void encode_symbol( FILE *stream, SYMBOL *s, unsigned int &bytesEscritos,unsigned int &bitsAcumulados );
void flush_arithmetic_encoder( FILE *stream );
short int get_current_count( SYMBOL *s );
