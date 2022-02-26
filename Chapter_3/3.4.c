#include <stdio.h>
#include <string.h>
#define MAX 100
/*In a two's complement number representation, our version of itoa does not handle the largest negative number, that is, the value of n equal to -(2 to the power (wordsize - 1)) . Explain why not. Modify it to print that value correctly regardless of the machine on which it runs.
*/
void reverse (char[]);
void itoa(int, char[]);

int main(void)
{
    int n = -2147483648;
    char array[MAX];

    itoa(n, array);
    printf("\n%s\n", array);

    return 0;
}

void itoa (int n, char array[])
{
    int i = 0;
    int sign = 0;

    if ((sign = n) < 0) // if int is negative, convert into positive
    {
        n = -n + 1; // -2147483648 > -2147483647
        n = -n; //-2147483647 > 2147483647 (limit of signed int)
        printf("%d\n", n);
    }
    do
    {
        printf("%c ", array[i++] = n % 10 + '0');
        /*
        2147483647 % 10 > 7 + '0' = char 7.
        */

    } while ((n /= 10) > 0); //division of 2147483647 / 10 cuts the rightmost number 1 by 1 : 7, 4, 6, etc.

    if (sign < 0)
    {
        array[i++] = '-'; // saving '-' char
    }
    array[i] = '\0';

    reverse(array);
}
void reverse (char array[])
{
    int c = 0;
    int i = 0;
    int j = 0;

    for (i = 0, j = strlen(array) - 1; i < j; i++, j--)
    {
        c = array[i];
        array[i] = array[j];
        array[j] = c; // reverse cycle reverses elements in half due to i++, j--

    }
    array[strlen(array) - 1] += 1; // -2147483647 + 1 > 2147483648
}