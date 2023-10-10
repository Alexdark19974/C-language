#include <stdio.h>

int add(int, int );

int main(int argc, char **argv) 
{
    int (*addp) (int, int);
    int a = 10;
    int b = 5;
    /* int c = 7 */
    // int j = 0;
    addp = add;
    addp(a, b);

    return 0;
}

int add(int a, int b)
{
    return printf("ret=%d\n", a + b);
}
