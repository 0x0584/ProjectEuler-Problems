/* FILE:	utils.c
 * AUTHOR:	ANAS RCHID
 * DESCRIPTION:	NULL
 *
 * CREATION:	06/13/2018
 * MODIFIED:	06/15/2018
 */

#include "../include/utils.h"

#define LIMIT (2000)
#define s
/* stdout, stderr */
#define STREAM stdout

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

list_t *tolist(array_t * array) {
    list_t *bar = new_list();
    size_t i = 0;

    for (; i < array->size; ++i) {
	push(bar, array->values[i]);
    }

    return bar;
}

array_t *toarray(list_t * list) {
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

void testing_array(FILE * stream) {
    array_t *arr = new_array(10), *brr = NULL;
    list_t *foo = NULL;
    size_t i = 0;

    fputs("\nTESTING ARRAY FUNCTIONALITIES\n", stream);

    for (; i < arr->size; ++i) {
	arr->values[i] = i;
    }
    output_array(stream, arr);

    foo = tolist(arr);
    output_list(stream, foo);

    brr = toarray(foo);
    output_array(stream, brr);

    free_list(foo);
    free_array(arr);
    free_array(brr);
}

void testing_list(list_t * foo, FILE * stream) {
    bool_t ishead = true;
    size_t value = 2;
    node_t *tmp0;
    long long tmp;

    fputs("TESTING LIST FUNCTIONALITIES:", stream);
    output_list(stream, foo);

    push(foo, 5);
    output_list(stream, foo);

    pusha(foo->tail, 2);
    output_list(stream, foo);

    pushb(foo->head, 1);
    output_list(stream, foo);

    tmp0 = find(foo, value, ishead);

    if (tmp0) {
	fprintf(stream, "find (%s) [%lld]\n",
		ishead ? "after" : "before", tmp0->value);
    } else {
	fprintf(stream, "%lu not found\n", value);
    }

    tmp = pop(foo);

    fprintf(stream, "[%lld] len %lu\n", tmp, length_list(foo));
    tmp = pop(foo);
    fprintf(stream, "[%lld] len %lu\n", tmp, length_list(foo));
    tmp = pop(foo);
    fprintf(stream, "[%lld] len %lu\n", tmp, length_list(foo));
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

bool_t isprime(size_t number) {
    size_t i = 2;

    for (; i <= number / 2; ++i) {
	if (!(number % i)) {
	    return false;
	}
    }

    return true;
}

list_t *getprimes(size_t limit) {
    list_t *tmp = new_list();
    size_t i = 2;

    for (; i <= limit; ++i) {
	if (isprime(i)) {
	    push(tmp, i);
	}
    }

    return tmp;
}

long long **decompose(size_t number, size_t * size) {
    enum { PRIME = 0, POWER = 1 };

    list_t *primes = NULL;
    size_t nprimes = 0, i = 0;
    long long **decompo = NULL;

    primes = getprimes(number);
    nprimes = *size = length_list(primes);
    decompo = malloc(nprimes * sizeof *decompo);

    /* pass through all primes */
    for (i = 0; !isempty_list(primes); ++i) {
	decompo[i] = malloc(2 * sizeof **decompo);
	decompo[i][PRIME] = popb(primes->tail);
	decompo[i][POWER] = 0;
	fprintf(stderr, "[%lld][%lld]\n", decompo[i][PRIME],
		decompo[i][POWER]);
    }

    fprintf(stderr, "----------------\n");

    free_list(primes);

    for (i = 0; i < nprimes; ++i) {
	long long tmp = decompo[i][PRIME];
	while (number % tmp == 0) {
	    decompo[i][POWER]++;
	    tmp *= tmp;
	    fprintf(stderr, "[%lld][%lld]\n",
		    decompo[i][PRIME], decompo[i][POWER]);
	}
    }

    return decompo;
}

void testing_primes(FILE * stream) {
    const char *filename = "primes.txt";

    size_t i = 0, limit = LIMIT, size = 0, random = rand()%limit;
    list_t *tmp = getprimes(limit);
    long long **d = NULL;
    FILE *file = NULL;

    fputs("TESTING PRIME NUMBERS FUNCTIONALITIES:\n", stream);
    fprintf(stream, "%ld %s\n", random, isprime(random) ? "true" : "false");
    fprintf(stream, "limit:%lu listlength:%lu", limit, length_list(tmp));

    file = fopen(filename, "w");
    output_list(file, tmp);
    fprintf(stream, ">%s\n", filename);

    output_list(stream, tmp);
    d = decompose(limit, &size);

    fprintf(stream, "%lu is written as:\n", limit);

    for (i = 0; i < size; ++i) {
	if (d[i][1]) {
	    fprintf(stream, "%lld to power of %lld\n", d[i][0], d[i][1]);
	}
    }

    for (i = 0; i < size; ++i) {
	free(d[i]);
    }

    free(d);
    free_list(tmp);
    fclose(file);
}

int main() {
    const char *filename = "output.txt";
    srand(time(NULL));
    /* FILE *stream = STREAM; */

    FILE *stream = fopen(filename, "w");

    /* list_t *r = random_list(0), *l = new_list(); */

    /* testing_list(l, stream); */
    /* free_list(l); */
    /* output_list(stream, r); */
    /* free_list(r); */
    /* testing_array(stream); */

    testing_primes(stream);

    fclose(stream);
}
