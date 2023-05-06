#include "linesort.h"

char *lineptr[MAXLINES];    /* pointers to text lines */

/* sort input lines */
main(int argc, char **argv)
{
    int nlines, field_length = -1;         /* number of input lines read */
    enum opt opt = NONE;
    while(*++argv) {
        if ((**argv == '-' && *(*argv + 1) && !isdigit(*(*argv + 1)))) {
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
                    case 'l':
                        opt|=FIELD_LENGTH;
                        break;
                    default:
                        if (**argv == '-') {
                            if (strstr(--*argv, "--help")) {
                                print_usage();
                                return 0;
                            }
                        }
                        if (**argv) {
                            printf("error: unknown option: %s", --*argv);
                            goto error;
                        }
                }
            }
        }
        else if ((isdigit(**argv) && (opt & FIELD_LENGTH)))
            field_length = atoi(*argv);
        else {
            printf("error: unknown option : %s. Maybe, you forgot to include \"-l\" option or you added a negative value?\n", *argv);
            goto error;
        }
    }
    if ((opt & FIELD_LENGTH) && field_length <= 0)
        printf("Warning: zero value used. Defaults to 1\n field_length = %d\n", field_length = 1);
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        _qsort((void **) lineptr, 0, nlines - 1, (int (*)(void *, void *, int, enum opt)) _strcmp_ext, opt, field_length);
        writelines(lineptr, nlines);
        while (nlines-- > 0) {
            afree(lineptr[nlines]);
            printf("freed ptr at index %d\n", nlines);
        }
        return 0;
    } else {
        printf("error: input too big to sort\n");
        goto error;
    }
error:
    return -1;
}
