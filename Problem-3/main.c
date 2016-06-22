        /* anasrchid - fall 2016 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static inline bool
isprime (long long unsigned int num)
{
	long long unsigned int i = 1;
	if (num <= 0 || num == 1) return 0;
	while (++i < num)
		if (num%i == 0) return 0;
	return 1;
}

int
main (int argc, char **argv)
{
	int divs[0x80] = {0};
	long long unsigned int i, k = 0, target = 100;
	
	if (argc == 2) target = atoi(argv[1]);
	for (i = 2; i < target; i += 1) 
		if(target%i == 0)
			if (isprime(i))
				divs[k++] = i;
	printf("%llu: ", target);
	for (i = 0; i < k; i += 1) 
		printf("%4d", divs[i]);
	putchar('\n');
	return 0;
}
