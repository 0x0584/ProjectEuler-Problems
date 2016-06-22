        /* anasrchid - fall 2016 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

size_t reverse(size_t num)
{
    size_t n = 0;
    while (num != 0)
    {
        size_t digit = num % 10;
        n = n * 10 + digit;
        num /= 10;
    }
    return n;
}
bool ispalin(size_t num)
{
	if(reverse(num) == num) return 1;
	return 0;
}
int main()
{
    size_t largest = 0;
    for (size_t a = 999; a >= 100; a--)
        for (size_t b = 999; b >= a; b--)
        {
            size_t product = a * b;
            if (product > largest && ispalin(product)) largest = product;
        }

    printf("%d\n", largest);
    return 0;
}
