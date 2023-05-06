#include "linesort.h"

char *lineptr[MAXLINES];    /* pointers to text lines */

/* sort input lines */
main()
{
    char linebuf[BUFSIZE] = {0};
    int nlines;     /* number of input lines read */

    if ((nlines = readlines(lineptr, linebuf, MAXLINES)) >= 0) {
        qsort(lineptr, 0, nlines - 1);
        writelines(lineptr, nlines);
      /*  while (nlines-- > 0) {
            afree(lineptr[nlines]);
            printf("freed ptr at index %d\n", nlines);
        } */
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}
