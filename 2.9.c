#include  <stdio.h>
int bitcount (unsigned int);
/*
In a two's complement number system, x &= (x-1) deletes the rightmost 1-bit in x . Explain why. Use this observation to write a faster version of bitcount .
*/
// x = x & (x - 1) > x &= (x - 1);
/*int main (void)
{
    char x = 7;  //00000111
    x &= (x - 1); //00000111 & (7  - 1) > 00000111 & 00000110 > 00000110 > 6

    printf("%d\n", x);

    return 0;
}*/

int main (void)
{
    int number = 128; //10000000
    printf("%d\n", bitcount(number));
    return 0;
}
int bitcount (unsigned int x)
{
    int b;
    for (b = 0; x != 0; x &= (x - 1))
    { 
        b++;
    }

    return b;
}
// 7 
//00000111 & 00000110 > 00000110 > 6
//00000110 & 00000101 > 00000100 > 4
//00000100 & 00000011 > 00000000 > 0

//128
//10000000 & 01111111 > 0 

/*int bitcount (unsigned int x)
{
    int b;
    for (b = 0; x != 0; x >> 1)
    {
        if (x & 01) 
        {
            b++;
        }
    }

    return b;
}*/