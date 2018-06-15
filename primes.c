/* FILE:	primes.c
 * AUTHOR:	ANAS RCHID
 * DESCRIPTION:	set of prime numbers utilities
 *
 * CREATION:	06/12/2018
 * MODIFIED:	06/12/2018
 */

#include <math.h>
#include "utils.h"

/**
 * Determine whether the number is prime or not
 *
 * @return true if the n is prime
 */
bool_t isprime(long n) {
    long i, limit = n/2;	/* if !logical to keep looking
				 * after n/2 */

    for (i = 2; i < limit; ++i) {
	unless (n%i) {		/* if n is divisible by i */
	    return false;
	}
    }

    return true;
}
