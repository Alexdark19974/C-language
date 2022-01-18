#include <stdio.h>
#define SWAP(t, x, y) \
{\
    t temp = x;\
    x = y;\
    y = temp;\
\
    printf("%g %g", x, y);\
}

/*Define a macro swap(t,x,y) that interchanges two arguments of type t . (Block structure will help.)*/

int main(void)
{
    int ar_1 = 12;
    int ar_2 = 9;
    SWAP(int, ar_1, ar_2);
}