#include "linesort.h"

char *lineptr[MAXLINES];    /* pointers to text lines */

/* sort input lines */
main(int argc, char **argv)
{
    int nlines;         /* number of input lines read */
    enum opt opt = NONE;
    while(*++argv) {
        if (**argv == '-' && *(*argv + 1) && !isdigit(*(*argv + 1))) {
            while (**argv) {
                switch (*++*argv) {
                case 'n':
                    opt|=NUMERIC;
                    break;
                case 'r':
                    opt|=REVERSE;
                    break;
                case 'f':
                    opt|=FOLD;
                    break;
                case 'd':
                    opt|=DIRECTORY_ORDER;
                    break;
                default:
                    if (**argv == '-' && *(*argv + 1) == '-') {
                        if (strstr(*argv, "--help")) {
                            print_usage();
                            return 0;
                        }
                    }
                    printf("error: unknown option: %s\n", --*argv);
                    goto error;
                }
            }
        }
        else {
            printf("error: unknwon option %s\n", *argv);
            goto error;
        }
    }
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        _qsort((void **) lineptr, 0, nlines - 1, (int (*)(void *, void *, enum opt)) _strcmp_ext, opt);
        writelines(lineptr, nlines);
        while (nlines-- > 0) {
            afree(lineptr[nlines]);
            printf("freed ptr at index %d\n", nlines);
        }
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
error:
    return -1;
}
