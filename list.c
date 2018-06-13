#include "utils.h"

list_t *init_list(void);
void free_list(list_t * list);
void push(list_t * list, int value);
void pushat(node_t * node, int value);
int pop(list_t * list);
int popat(node_t * node);
node_t *find(list_t *list, int value);
node_t *findfar(list_t *list, int value);

array_t *init_array(void);
void free_array(array_t * array);

list_t *tolist(array_t * array);
array_t *toarray(list_t * list);
