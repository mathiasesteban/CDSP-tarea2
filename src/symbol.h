#ifndef SYMBOL_H
#define SYMBOL_H


// Symbol header, defines the general symbol structure used in
// the proccess


/*
 * A symbol can either be represented as an int, or as a pair of
 * counts on a scale.  This structure gives a standard way of
 * defining it as a pair of counts.
 */
typedef struct  {
                unsigned short int low_count;
                unsigned short int high_count;
                unsigned short int scale;
               } SYMBOL;


struct {
         char c;
         unsigned short int low;
         unsigned short int high;
      } probabilities[]= {{ '0',  0,  1  },
                          { '1',  1,  4  },
                          { '\0', 4, 5  }
                         };


#endif
