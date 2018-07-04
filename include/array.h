#ifndef __ARRAY_H
#  define __ARRAY_H
#  include "general.h"

/**
 * Array data structure, basically for storing integers
 * */
typedef struct ARRAY {
    int *values;		/* the actual array */
    size_t size;		/* the size of the array */
} array_t;

/* ------------- prototypes ------------- */
array_t *init_array(void);
void free_array(array_t * array);

#endif
