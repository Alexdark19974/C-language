#include <stdio.h>

main()
{
    int c;

    while((c = getchar()) != EOF)
        putchar(c);
    printf("EOF=%d\n", c);
}

