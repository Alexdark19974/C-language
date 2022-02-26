#include <stdio.h>

//Exercise 2-6. Write a function setbits(x,p,n,y) that returns x with the n bits that begin at position p set to the rightmost n bits of y, leaving the other bits unchanged.



unsigned int setbits(unsigned int, int, int, unsigned int);

int main (void)
{
    int number = 82;     //010|100|10 = 01010110
    int op_number = 13; // 00001|101| 
    int bitmap = 3;
    int position = 4;
    
    int got_bits = setbits(number, position, bitmap, op_number);

    printf("%d\n", got_bits);

    return 0;
}
unsigned int setbits(unsigned int x, int p, int n, unsigned int y)
{
    int tmp1 = ((~(~0 << n)) & y) << (p + 1 - n);
    /*
    00000000
    11111111
    11111000
    00000111
    00001101 & 00000111 = 00000101
    00000101 << 2 = 00010100
    */
    int tmp = x & (~(~(~0 << n) << (p + 1 - n)));
    /*
    00000000
    11111111
    11111000
    00000111
    00011100
    11100011 & 01010010 = 01000010
    */
    return tmp | tmp1;
    /*
    00010100 | 01000010 = 01010110
    */
}