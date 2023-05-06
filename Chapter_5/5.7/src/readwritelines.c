#include "linesort.h"

/* readlines:  read input lines */
int readlines(char *lineptr[], char *linebuf, int maxlines)
{
    int len, nlines;
    static int bufctr = 0;
    char /**p,*/ line[MAXLEN];

    nlines = 0;
    while((len = get_line(line, MAXLEN)) > 0)
        if (nlines >= maxlines || bufctr >= BUFSIZE - 1/*(p = alloc(len)) == NULL*/)
            return -1;
        else {
            line [len-1] = '\0'; /* delete newline */
            bufctr == 0 ? strcpy(linebuf, line) : strcpy(&linebuf[bufctr], line);
            bufctr+=len;
            lineptr[nlines++] = &linebuf[bufctr - len];
        }
    return nlines;
}

/* writeline:  write output lines */
void writelines(char *lineptr[], int nlines)
{
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
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
