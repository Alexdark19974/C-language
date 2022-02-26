#include <stdio.h>
#include <string.h>
#define MAX 100
void reverse (char[]);
void itoa(int, char[], int);
/*
Write a version of itoa that accepts three arguments instead of two. The third argument is a minimum field width; the converted number must be padded with blanks on the left if necessary to make it wide enough.
*/
int main(void)
{ 
    int n = 123;
    char array[MAX];
    int width = 4;

    itoa(n, array, width);
    printf("%s\n", array);

    return 0;
}

void itoa (int n, char array[], int width)
{
    int i = 0;
    int sign = 0;

    if ((sign = n) < 0)
    {
        n = -n;
    }

    do
    {
        array[i++] = n % 10 + '0';

    } while ((n /= 10) > 0);

    if (sign < 0)
    {
        array[i++] = '-';
    }

    array[i] = '\0';

    reverse(array);

     if (i < width)
    {
        for (i = i; i != width; i++)
        {
            array[i] = 'b';
        }
    }
    else if (i > width)
    {
        int cut = i - width;
        array[i - cut] = '\0';
    }
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
        array[j] = c;
    }
}