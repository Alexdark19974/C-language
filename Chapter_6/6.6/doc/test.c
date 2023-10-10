#include <stdio.h>

#define TRUE
#define FALSE 0
#define ARG1 100
#define ARG2 200
#define DATA "data"
#define TIME "forever"
#define EVER "FOREVER"
#define TWO "two"
#define ONE TWO
#define AMON_AMARTH "death to all jews"
#define HAPPINES 0
int main(void) 
{
    int a = ARG1;
    int b = ARG2;
    int c = a + b;
    char *pstr = DATA;
    printf("res=%d\n", c);
    printf("str=%s\n", pstr);
    printf("ONE=%s\n", ONE);
    return 0;
}

