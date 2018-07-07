#ifndef __ARRAY_H
#  define __ARRAY_H
#  include "general.h"

/**
 * Array data structure, basically for storing integers
 * */
typedef struct ARRAY {
    long long *values;		/* the actual array */
    size_t size;		/* the size of the array */
} array_t;

/* ------------- prototypes ------------- */
array_t *new_array(size_t size);
void free_array(array_t * array);
void output_array(FILE * stream, array_t * arr);
#endif
