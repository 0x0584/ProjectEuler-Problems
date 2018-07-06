/* FILE:	utils.c
 * AUTHOR:	ANAS RCHID
 * DESCRIPTION:	NULL
 *
 * CREATION:	06/13/2018
 * MODIFIED:	07/05/2018
 */

#include "../include/utils.h"

array_t *new_array(size_t size) {
    array_t *tmp = malloc(sizeof *tmp);

    tmp->size = size;
    tmp->values = malloc(size * sizeof *tmp->values);

    return tmp;
}

void free_array(array_t * array) {
    free(array->values);
    free(array);
}

list_t *to_list(array_t * array) {
    list_t *bar = new_list();
    size_t i = 0;

    for (; i < array->size; ++i) {
	push(bar, array->values[i]);
    }

    return bar;
}

array_t *to_array(list_t * list) {
    size_t size = length_list(list);
    array_t *bar = new_array(size);
    node_t *tmp = list->head->next;

    while (tmp->next) {
	bar->values[bar->size - size--] = tmp->value;
	tmp = tmp->next;
    }

    return bar;
}

void output_array(FILE * stream, array_t * array) {
    size_t i = 0;

    for (; i < array->size; ++i) {
	fprintf(stream, "[%lu] %lld\n", i, array->values[i]);
    }
}
