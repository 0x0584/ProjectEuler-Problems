#ifndef __GENERAL_H
#  define __GENERAL_H
#  define unless(x) if(!(x))
#  include <stdio.h>
#  include <stdlib.h>

/**
 * who said C has no booleans?
 */
typedef enum BOOLEAN {
    false = (1 == 0),
    true = !false
} bool_t;

#endif
