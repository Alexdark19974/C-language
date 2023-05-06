#include "tail.h"

/* readlines:  read input lines */
int readlines(char *lineptr[], char *linebuf, int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while((len = get_line(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else {
            line [len-1] = '\0'; /* delete newline character */
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    return nlines;
}

int get_line(char *s, int lim)
{
    int i, c = 0;

    for (i = 0; (i < lim) && ((c = getchar()) != EOF) && (c != '\n'); ++i)
        *(s + i) = c;
    if (c =='\n')
        *(s + i) = c, i++;

    *(s + i) = '\0';
    return c == EOF ? EOF : i;
}
