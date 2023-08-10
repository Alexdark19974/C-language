#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#define MAXLINE 100
void minprintf(char *, ...);
typedef unsigned int uint;
main()
{
    printf("standard printf: ");
    printf(":%*s: %u %g\n", -1, "Hello", 1, 5.7);
    printf("      minprintf: ");
    minprintf(":%*s: %u %g\n", 10, "Hello", 1, 5.7);
    return 0;
}

/* minprintf: minimal printf with variable argument list */
void minprintf(char *fmt, ...)
{
    va_list ap;     /* points to each unnamed arg in turn */
    char *p, *tmpsval, *sval, *tmpBuf = calloc(1, MAXLINE);
    int ival, i = 0;
    uint uival;
    double dval;

    if (!tmpBuf) {
        printf("error: failed to alloc %d for tmpBuf\n", MAXLINE);
        return;
    }

    va_start(ap, fmt); /* make ap point to 1st unnamed arg */
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }
jump_to_symbol:
        switch (*++p) {
            case 'u':
                uival = va_arg(ap, unsigned int);
                printf("%u", uival);
                break;
            case 'i':
            case 'd':
                ival = va_arg(ap, int);
                printf("%d", ival);
                break;
            case 'f':
                dval = va_arg(ap, double);
                printf("%f", dval);
                break;
            case 'g':
                dval = va_arg(ap, double);
                printf("%g", dval);
                break;
            case 's':
                for (sval = va_arg(ap, char *), tmpsval = sval; *sval; sval++) {
                    if (!*tmpBuf)
                        putchar(*sval);
                }
                if (*tmpBuf)
                    printf("%*s", atoi(tmpBuf), tmpsval);
                tmpBuf[0] = '\0';
                break;
            case '*':
                ival = va_arg(ap, int);
                sprintf(tmpBuf, "%d", ival);
                goto jump_to_symbol;
                break;
            default:
                if (isdigit(*p) || (*p == '-' && isdigit(*(p + 1)))) {
                    tmpBuf[i++] = *p++;
                    while(isdigit(*p))
                        tmpBuf[i++] = *p++;
                    tmpBuf[i] = '\0', i = 0;
                    p--;
                    goto jump_to_symbol;
                }
                putchar(*p);
                break;
        }
    }
    free(tmpBuf);
    tmpBuf = NULL;
    va_end(ap);    /* clean up when done */
}
