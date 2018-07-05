#include "../include/utils.h"

void testing_array(FILE * stream);
void testing_list(list_t * foo, FILE * stream);
void testing_primes(FILE * stream);

bool_t isprime(size_t number);
list_t *getprimes(size_t limit);
long long **decompose(size_t number, size_t * size);

int main() {
    const char *log = "output.txt";
    srand(time(NULL));
    /* FILE *stream = STREAM; */

    FILE *stream = fopen(log, "w");

    /* list_t *r = random_list(0), *l = new_list(); */

    /* testing_list(l, stream); */
    /* free_list(l); */
    /* output_list(stream, r); */
    /* free_list(r); */
    /* testing_array(stream); */

    testing_primes(stream);

    fclose(stream);
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
	/* fprintf(stderr, "[%lld][%lld]\n", decompo[i][PRIME], */
	/*	decompo[i][POWER]); */
    }

    /* fprintf(stderr, "----------------\n"); */

    free_list(primes);

    for (i = 0; i < nprimes; ++i) {
	long long tmp = decompo[i][PRIME];
	while (number % tmp == 0) {
	    decompo[i][POWER]++;
	    tmp *= tmp;
	    /* fprintf(stderr, "[%lld][%lld]\n", */
	    /* decompo[i][PRIME], decompo[i][POWER]); */
	}
    }

    return decompo;
}


void testing_primes(FILE * stream) {
    const char *filename = "primes.txt";

    size_t i = 0, limit = LIMIT, size = 0, random = rand() % limit;
    list_t *tmp = getprimes(limit);
    long long **d = NULL;
    FILE *file = NULL;

    fputs("TESTING PRIME NUMBERS FUNCTIONALITIES:\n", stream);
    fprintf(stream, "%ld %s\n", random,
	    isprime(random) ? "true" : "false");
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
