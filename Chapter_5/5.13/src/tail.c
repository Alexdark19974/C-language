#include "tail.h"

void tail(char **lineptr, int n, int nlines)
{
    int i;

    if (n > nlines)
        n = nlines;
    printf("tail:\n");
    for (i = nlines - n; i < nlines; i++)
        printf("%d %s\n", i, *(lineptr  + i));
}
