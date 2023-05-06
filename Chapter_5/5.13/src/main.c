#include "tail.h"

main(int argc, char **argv)
{
    char *lineptr[MAXLINES] = {NULL}; /* pointers to text lines */

    char linebuf[BUFSIZE] = {0};
    int nlines, n = -1;     /* number of input lines read */

    while(*++argv) {
        if (**argv == '-') {
            switch(*++*argv) {
                case 'n':
                    if (0 >= (n = atoi(*++argv)))
                            goto error;
                    break;
                default:
                    printf("error: unknown option.\n");
                    goto error;
                    break;
            }
        }
        else
            return printf("error: unknown option = %s\n", *argv);
    }
    if ((nlines = readlines(lineptr, linebuf, MAXLINES)) >= 0) {
        tail(lineptr, n == -1 ? DEFAULTTAILLEN : n, nlines);
        afree(lineptr[nlines]);
        printf("freed ptr at index %d\n", nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
error:
    return printf("error: check the length (n = %d) of your readlines or args(argv = %s)\n", n, --*argv);
}
