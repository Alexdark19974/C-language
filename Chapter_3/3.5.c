#include <stdio.h>
#include <string.h>
#define MAX 100
void itob (unsigned int, unsigned char[], unsigned int);
void reverse (unsigned char[]);

/*
Write the function itob(n,s,b) that converts the integer n into a base b character representation in the string s. In particular, itob(n,s,16) formats s as a hexadecimal integer in s.
*/

int main(void)
{
    unsigned int n = 127;
    unsigned int b = 3;
    unsigned char array[MAX];

    itob(n, array, b);
    printf("%s\n", array);

    return 0;
}
void itob (unsigned int n, unsigned char array[], unsigned int b)
{
    int i = 2;
    int j = 0;
    char const hex[] = "0123456789abcdef";
    char const bin[] = "01";

    switch (b)
    {
        case 16:
        {
            array[0] = '0';
            array[1] = 'x';

            do
            {
                printf("%d ", n);
                int remainder = n % 16;
                printf("%d ", remainder);
                
                if (remainder >= 0 && remainder <= 15)
                {
                    for (int f = 0; hex[f] != '\0'; f++)
                    {
                        if (remainder == f)
                        {
                            array[i++] = hex[f];
                        } 
                    }   
                }
            }
            while ((n = n/b) > 0);

            array[i] = '\0';

            reverse (array);

            break;           
        }
        case 2:
        {
            array[0] = '0';
            array[1] = 'b';

            do
            {
                int remainder = n % 2;

                if (remainder == 0 || remainder == 1)
                {
                    for (int f = 0; bin[f] != '\0'; f++)
                    {
                        if (remainder == f)
                        {
                            array[i++] = bin[f];
                        } 
                    }   
                }
            }
            while ((n = n/b) > 0);
            array[i] = '\0';
            reverse (array);
            break; 
        }
        default :
        {
            break;
        }
    }
}
void reverse (unsigned char array[])
{
    int c = 0;
    int i = 0;
    int j = 0;

    for (i = 2, j = strlen(array) - 1; i < j; i++, j--)
    {
        c = array[i];
        array[i] = array[j];
        array[j] = c;

    }
}