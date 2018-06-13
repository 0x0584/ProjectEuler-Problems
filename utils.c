#include "utils.h"

list_t *init_list(void) {
    list_t *foo;
    node_t *head, *tail;

    head = malloc(sizeof *head);
    tail = malloc(sizeof *tail);

    head->prev = NULL;
    head->value = -1;
    head->next = tail;

    tail->prev = head;
    tail->value = -1;
    tail->next = NULL;

    foo = malloc(sizeof *foo);
    foo->head = head;
    foo->tail = tail;

    return foo;
}

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

bool_t isempty_list(list_t * list) {
    return list->head->next == list->tail;
}

void print_list(list_t * list) {
    node_t *tmp = list->head->next;

    while (tmp->next) {
	tmp = tmp->next;
	printf("%d ", tmp->value);
    }

    putchar('\n');
}

void push(list_t * list, int value) {
    pusha(list->head, value);
}

void pusha(node_t * node, int value) {
    node_t *new = malloc(sizeof *new);

    new->value = value;

    if (!node->next) {		/* this is the tail */
	pushb(node, value);
    } else {
	new->prev = node;
	new->next = node->next;
	node->next = new;
    }
}

void pushb(node_t * node, int value) {
    node_t *new = malloc(sizeof *new);

    new->value = value;

    if (!node->prev) {		/* this is the head */
	pusha(node, value);
    } else {
	new->prev = node->prev;
	new->next = node;
	node->prev = new;
    }
}

int pop(list_t * list);
int popa(node_t * node);
int popb(node_t * node);
node_t *find(list_t * list, int value);
node_t *findfar(list_t * list, int value);

array_t *init_array(void);
void free_array(array_t * array);

list_t *tolist(array_t * array);
array_t *toarray(list_t * list);

int main() {
    list_t *foo = init_list();

    print_list(foo);
    push(foo, 5);
    print_list(foo);
    pusha(foo->tail, 3);
    print_list(foo);
    pushb(foo->head, 2);

    print_list(foo);

    free_list(foo);
}
