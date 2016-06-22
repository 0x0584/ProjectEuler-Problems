        /* anasrchid - fall 2016 */

#include <stdio.h>
#include <stdlib.h>

int
main (int argc, char **argv)
{
	int s = 0, lim = 10;
	if (argc == 2) lim = atoi(argv[1]);
	for (int i = 1; i < ; i += 1)
		if (!(i%3) || !(i%5))
			s += i; 
	printf("%d\n", s);
	return 0;
}
