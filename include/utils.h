#ifndef __UTILS_H
#  define __UTILS_H
#  define JUNK_DATA (INT_MAX)
#  define LIMIT (20)		/* set this as you like to change the input prime */
#  define STREAM stdout		/* stdout, stderr */
#  include "list.h"
#  include "array.h"
#  include <limits.h>
#  include <time.h>

list_t *init_list(array_t * array);
list_t *to_list(array_t * array);
array_t *to_array(list_t * list);

#endif
