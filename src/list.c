#include "../include/utils.h"

node_t *new_node(long long value, node_t * prev, node_t * next) {
    node_t *new = malloc(sizeof *new);

    new->value = value;
    new->prev = prev;
    new->next = next;

    return new;
}

void free_node(node_t * node) {
    free(node);
}

/**
 * creates a new list
 *
 * @return a new empty list
 * @notes  must call free_list() to free the list from the memory
 */
list_t *new_list(void) {
    list_t *foo;
    node_t *head = new_node(JUNK_DATA, NULL, NULL);
    node_t *tail = new_node(JUNK_DATA, NULL, NULL);

    head->next = tail;
    tail->prev = head;

    foo = malloc(sizeof *foo);
    foo->head = head;
    foo->tail = tail;

    return foo;
}

/**
 * creates a new list, memory is allocated used new_list().
 * then fill the it with the elements of the passed array.
 *
 * @param  array an array_t
 * @return a new list with all the elements in the `array`
 */
list_t *init_list(array_t * array) {
    list_t *foo = new_list();
    size_t i = 0;

    for (i = 0; i < array->size; ++i) {
	push(foo, array->values[i]);
    }

    return foo;
}

/**
 * deallocate `list` from memory.
 *
 * @param list a list_t to set free
 * @notes after calling this function list is not accessible
 */
void free_list(list_t * list) {
    node_t *tmp, *head = list->head;

    /* another approach would be using pop() but this one
     * is more efficiant since it's just permutation of node */
    while (!isempty_list(list)) {
	tmp = head->next;
	head->next = tmp->next;
	free(tmp);
    }

    free(list->head);
    free(list->tail);
    free(list);
}

/**
 * indicates the state of the list, whether it is empty or not
 *
 * @param  list a list_t to check
 * @return true is the list is empty
 */
bool_t isempty_list(list_t * list) {
    return list->head->next == list->tail;
}

/**
 * gives the length of the list, i.e. how many elements are there
 *
 * @param  list a list_t to count
 * @return the length of the list
 * @notes  this is sillym we have to go over the whole list.
 *	   is there any more efficiant way?
 */

size_t length_list(list_t * list) {
    node_t *tmp = list->head->next;
    size_t count = 0;

    while (tmp->next) {
	++count;
	tmp = tmp->next;
    }

    return count;
}

/**
 * writes the `list` on the `stream` whether standard ones
 * such as stdout and strerr or any other `FILE` stream
 *
 * @param stream a FILE stream to output in
 * @param list a list_t to output
 */
void output_list(FILE * stream, list_t * list) {
    node_t *tmp = list->head->next;
    size_t count = 0;

    fputc('[', stream);

    while (tmp->next) {
	fprintf(stream, "%lld", tmp->value);
	tmp = tmp->next;
	if (tmp->next) {
	    fputc(',', stream);
	    fputc(count++ % 10 == 9 ? '\n' : ' ', stream);
	}
    }

    fputc(']', stream);
    fputc('\n', stream);
}

/**
 * pushes the `value` into the `list`. it's basically a call
 * of pusha() with passing list->head as the node.
 *
 * @param  list a list_t to push into
 * @param  value an integer value to push
 * @return pointer to the pushed node
 * @notes  see pusha() for more details
 */
node_t *push(list_t * list, long long value) {
    return pusha(list->head, value);
}

/**
 * pushes the `value` to a new node and place it after the `node`.
 *
 * @param  node a node_t to push after
 * @param  value an integer value to push
 * @return pointer to the pushed node
 * @notes  if the node is a tail, then we push before using pushb()
 */
node_t *pusha(node_t * node, long long value) {
    node_t *tmp, *new;

    if (!node->next) {
	return pushb(node, value);	/* this is the tail */
    }

    new = new_node(value, node, node->next);

    tmp = node->next;
    node->next = new;
    tmp->prev = new;

    return new;
}

/**
 * pushes the `value` to a new node and place it before the `node`.
 *
 * @param  node a node_t to push before
 * @param  value an integer value to push
 * @return pointer to the pushed node
 * @notes  if the node is a head, then we push after using pusha()
 */
node_t *pushb(node_t * node, long long value) {
    node_t *tmp, *new;

    if (!node->prev) {
	return pusha(node, value);	/* this is the head */
    }

    new = new_node(value, node->prev, node);

    tmp = node->prev;
    node->prev = new;
    tmp->next = new;

    return new;
}


long long pop(list_t * list) {
    return popa(list->head);
}

long long popa(node_t * node) {
    node_t *tmp;
    long long data;

    if (!(tmp = node->next)) {
	return JUNK_DATA;
    }

    data = tmp->value;
    node->next = tmp->next;
    tmp->next->prev = node;

    free_node(tmp);

    return data;
}

long long popb(node_t * node) {
    node_t *tmp;
    long long data;

    if (!(tmp = node->prev)) {
	return JUNK_DATA;
    }

    data = tmp->value;
    node->prev = tmp->prev;
    tmp->prev->next = node;

    free_node(tmp);

    return data;
}

node_t *find(list_t * list, long long value, bool_t ishead) {
    node_t *tmp = NULL, *target = NULL;
    tmp = ishead ? list->head->next : list->tail->prev;

    while (tmp) {
	if (tmp->value == value) {
	    target = tmp;
	    break;
	} else {
	    tmp = ishead ? tmp->next : tmp->prev;
	}
    }

    /* for-version */
    /*
       for (; tmp;
       tmp = ishead ? tmp->next : tmp->prev) {
       if (tmp->value == value) {
       return tmp;
       }
       }
     */
    return target;
}

list_t *random_list(size_t limit) {
    list_t *tmp = new_list();
    size_t rand_seed = rand() % 0xFF, value;

    if (limit == 0) {
	limit = 15;
    }

    while (limit--) {
	value = rand() % rand_seed;
	push(tmp, value);
    }

    return tmp;
}

list_t *distinct_list(list_t *list) {
    return list;
}
