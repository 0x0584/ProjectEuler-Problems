#ifndef __LIST_H
#  define __LIST_H
#  include "general.h"

/**
 * Node, is a particular piece inside a `list_t` element
 * */
typedef struct NODE {
    int value;			/* content of the node */
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
list_t *new_list(void);
void free_list(list_t * list);
void output_list(FILE * stream, list_t * list);
bool_t isempty_list(list_t * list);
/* TODO: find another way to get the length, this is silly and no efficant */
int length_list(list_t * list);
node_t *push(list_t * list, int value);
node_t *pusha(node_t * node, int value);
node_t *pushb(node_t * node, int value);
int pop(list_t * list);
int popa(node_t * node);
int popb(node_t * node);
node_t *find(list_t * list, int value);
node_t *findfar(list_t * list, int value);

#endif
