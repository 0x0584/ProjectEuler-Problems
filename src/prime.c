#include "../include/utils.h"

#define DEFAULT_N 9
#define DEFAULT_M 2


void testing_array(FILE * stream);
void testing_list(list_t * foo, FILE * stream);
void testing_primes(FILE * stream);

bool_t isprime(size_t number);
list_t *getprimes(size_t limit);
size_t **decompose(size_t number, size_t * size);

list_t *getset(size_t m, size_t n) {
    fprintf(STREAM, "\n%ld-%ld\n", m, n);
    list_t *new = new_list();
    return new;
}

void testing_solution(size_t * input, size_t size) {
    const size_t bar = size / 2;
    size_t i = 0, m = 0, n = 0;
    for (i = 0; i < size; ++i) {
	fprintf(STREAM, "%lu\n", input[i]);
    }

    for (i = 0; i < bar; ++i) {
	list_t *S = getset((m = input[i]),
			   (n = input[bar + i]));
	/* output_list(STREAM, solution); */
	/* fprintf(STREAM, "F(%lu, %lu) = %lu", m, n, length_list(solution)); */

	free_list(S);
	puts("%");
    }
}

int main(int argc, char **argv) {
    srand(time(NULL));

    const char *log = "log.txt";
    const bool_t iseven = ((argc) % 2), isvalid = (argc - 3 >= 0);

    FILE *stream = false ? fopen(log, "w") : STREAM;
    size_t *input = NULL, bar = 1, i = 0;

    /* ----------- handling arguments ----------- */
    if (isvalid) {
	bar = iseven ? (argc) / 2: (argc - 1) / 2;
	if (!iseven) {
	    fputs("WARN:numbers should be sent as paires\n", stream);
	}
    } else {
	fputs("WARN:no valid input was sent, taking defaults", stream);
    }

    input = malloc(bar * 2 * sizeof *input);

    printf("bar:%lu isvalid:%s iseven:%s\n", bar,
	   isvalid ? "t" : "nil", iseven ? "t" : "nil");

    if (isvalid) {
	for (i = 0; i < bar; i++) {
	    input[i] = atoi(argv[i*2 + 1]);
	    input[bar + i] = atoi(argv[i*2 + 2]);
	}
	puts("%");
    } else {
	input[0] = DEFAULT_M;
	input[bar + 0] = DEFAULT_N;
    }

    /* --------------- testings ---------------- */

    /* list_t *r = random_list(0), *l = new_list(); */

    /* testing_list(l, stream); */
    /* free_list(l); */
    /* output_list(stream, r); */
    /* free_list(r); */
    /* testing_array(stream); */
    /* testing_primes(stream); */

    testing_solution(input, (bar * 2));

    fclose(stream);
    free(input);

    return EXIT_SUCCESS;
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

size_t **decompose(size_t number, size_t * size) {
    enum { PRIME = 0, POWER = 1 };

    size_t nprimes = 0, i = 0, **decompo = NULL;
    list_t *primes = NULL;

    /* 0. initialization */
    primes = getprimes(number);
    nprimes = *size = length_list(primes);
    decompo = malloc(nprimes * sizeof *decompo);

    for (i = 0; !isempty_list(primes); ++i) {
	decompo[i] = malloc(2 * sizeof **decompo);
	decompo[i][PRIME] = popb(primes->tail);
	decompo[i][POWER] = 0;
	/* // debugging
	   fprintf(stderr, "[%lld][%lld]\n", decompo[i][PRIME],
	   decompo[i][POWER]);
	 */
    }

    free_list(primes);
    /* fprintf(stderr, "----------------\n"); */


    /* 1. decompose: for all the primes */
    for (i = 0; i < nprimes; ++i) {
	size_t prime = decompo[i][PRIME];
	/* if the number is divisible by this prime */
	while (number % prime == 0) {
	    decompo[i][POWER]++;	/* increase power count */
	    prime *= decompo[i][PRIME];	/* move to the next power */

	    /* // debugging
	       fprintf(stderr, "[%lu][%lu]\n",
	       decompo[i][PRIME], decompo[i][POWER]);
	     */
	}
    }

    return decompo;
}


void testing_primes(FILE * stream) {
    const char *filename = "primes.txt";

    size_t i = 0, n = 0, limit = LIMIT, size = 0, random = rand() % limit;
    list_t *tmp = getprimes(limit);
    size_t **d = NULL;
    FILE *file = NULL;

    fputs("TESTING PRIME NUMBERS FUNCTIONALITIES:\n", stream);
    fprintf(stream, "%ld %s\n", random,
	    isprime(random) ? "true" : "false");
    fprintf(stream, "limit:%lu listlength:%lu", limit, length_list(tmp));

    file = fopen(filename, "w");
    output_list(file, tmp);
    fprintf(stream, ">%s\n", filename);

    output_list(stream, tmp);

    do {
	d = decompose(++n, &size);

	fprintf(stream, "%lu is written as:\n", n);

	for (i = 0; i < size; ++i) {
	    if (d[i][1]) {
		fprintf(stream, "%lu to power of %lu\n", d[i][0], d[i][1]);
	    }
	}

	for (i = 0; i < size; ++i) {
	    free(d[i]);
	}

	free(d);
	fputs("--------------------\n", stream);
    } while (n <= limit);

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

    foo = to_list(arr);
    output_list(stream, foo);

    brr = to_array(foo);
    output_array(stream, brr);

    free_list(foo);
    free_array(arr);
    free_array(brr);
}
