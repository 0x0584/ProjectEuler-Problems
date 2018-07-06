#ifndef __LIST_H
#  define __LIST_H
#  include "general.h"

/**
 * Node, is a particular piece inside a `list_t` element
 * */
typedef struct NODE {
    long long value;		/* content of the node */
    struct NODE *prev,		/* the that comes before this node */
       *next;			/* the node that comes after this node */
} node_t;

/**
 * List	data structure, is a sequence of `nodes`
 * */
typedef struct LIST {
    struct NODE *head,		/* the very first node in the list */
       *tail;			/* the very last node in the list */
} list_t;

/* ------------- prototypes ------------- */

node_t *new_node(long long value, node_t * prev, node_t * next);
void free_node(node_t * node);

list_t *new_list(void);
void free_list(list_t * list);
void output_list(FILE * stream, list_t * list);
bool_t isempty_list(list_t * list);
/* TODO: find another way to get the length,
 * this is silly and no efficant */
size_t length_list(list_t * list);
node_t *push(list_t * list,  long long value);
node_t *pusha(node_t * node, long long value);
node_t *pushb(node_t * node, long long value);
long long pop(list_t * list);
long long popa(node_t * node);
long long popb(node_t * node);
node_t *find(list_t * list, long long value, bool_t ishead);
void testing_list(list_t * list, FILE * stream);
list_t *random_list(size_t limit);
list_t *distinct_list(list_t *list);
#endif
