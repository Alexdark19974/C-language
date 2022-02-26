#include <stdio.h>
unsigned int invert (unsigned int, unsigned int, unsigned int);
/*Write a function invert(x,p,n) that returns x with the n bits that begin at position p inverted (i.e., 1 changed into 0 and vice versa), leaving the others unchanged.*/

int main(void)
{
    int number = 84; //0|0101|101 > 0|1010|101  > 85
    int position = 6;
    int bit_net = 4;
    printf("%d\n", invert(number, position, bit_net));
    return 0;
}

unsigned int invert ( unsigned int x, unsigned int p, unsigned int n)
{
    int tmp1 = ~(~0 << n); // 00000000 > 11111111 > 11110000 > 00001111
    tmp1 = (x >> (p + 1 - n)) & tmp1; // 00101101 > 0000|0101 & 00001111 > 0101
    tmp1 = ~tmp1; //00000101 > 1111|1010
    tmp1 = ((~0 << n) ^ tmp1) << (p + 1 - n); //11110000  ^ 1111|1010| > 00001010 > 0|1010|000
    int tmp = ~(~0 << n); //00000000 > 11111111 > 11110000 > 00001111
    tmp = tmp << (p + 1 - n); //01111000
    tmp = ~tmp; //10000111
    tmp = x & tmp; // 00101101 & 10000111 > 00000101;
    return tmp1 | tmp; // 01010000 | 00000101 > 01010101
}   

