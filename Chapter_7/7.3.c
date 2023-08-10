#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#define ON  1
#define OFF 0
#define OK 0
#define MAXLINE 100
enum errwarnCase { ERRNOMEM = -1, ERRARGNUM = -2, WARNARGNUM = -3, WARNNOARG = -4};
int minprintf(int, char *, ...);
void handle_err_warn(int, int);
typedef unsigned int uint;

main()
{
    int retVal = OK, argNum = 2;
    printf("standard printf: ");
    printf(":%.2s: %u %g\n", "Hello", 1, 5.7);
    printf("      minprintf: ");
    if ((retVal = minprintf(argNum,":%.2s: %u %g PUT HIM DOWN ON THE GROUND!\n", "Hello", 1, 5.7) != OK))
        handle_err_warn(retVal, argNum);
    return 0;
}

void handle_err_warn(int errWarn, int argNum)
{
    switch (errWarn)
    {
        case ERRNOMEM:
            printf("error: failed to alloc %d for tmpBuf\n", MAXLINE);
            break;
        case ERRARGNUM:
            printf("error: check the number of arguments.\n");
            break;
        case WARNARGNUM:
            printf("warning: skipping one of the format specifiers due to number of args is %d\n", argNum);
            break;
        case WARNNOARG:
            printf("warning: number of arguments=%d\n", argNum);
            break;
        case OK:
        default:
            break;
    }

}

/* minprintf: minimal printf with variable argument list */
int minprintf(int arg_num, char *fmt, ...)
{
    va_list ap;     /* points to each unnamed arg in turn */
    char *p, *tmpsval, *sval, *tmpBuf = NULL;
    int ival, i = 0, lenLim = 0,retVal = 0;
    uint uival;
    double dval;

    va_start(ap, fmt);

    if (arg_num <= 0) {
        va_end(ap);
        retVal = WARNNOARG;
        goto end;
    }
    if (!(tmpBuf = calloc(1, MAXLINE))) {
        retVal = ERRNOMEM;
        goto end;
    }

    va_start(ap, fmt); /* make ap point to 1st unnamed arg */
    for (p = fmt; *p; p++) {
        if (*p != '%' && *p != '.') {
            if(*(p - 1) != '%')
                putchar(*p);
            else
                retVal = WARNARGNUM;
            continue;
        }
        if (!arg_num)
            continue;
jump_to_symbol:
        switch (*++p) {
            case 'u':
                uival = va_arg(ap, unsigned int);
                printf("%u", uival);
                arg_num--;
                break;
            case 'i':
            case 'd':
                ival = va_arg(ap, int);
                printf("%d", ival);
                arg_num--;
                break;
            case 'f':
                dval = va_arg(ap, double);
                printf("%f", dval);
                arg_num--;
                break;
            case 'g':
                dval = va_arg(ap, double);
                printf("%g", dval);
                arg_num--;
                break;
            case 's':
                sval = va_arg(ap, char *);
                for (/*sval = va_arg(ap, char *),*/ tmpsval = sval; sval != NULL && *sval; sval++) {
                    if (!*tmpBuf)
                        putchar(*sval);
                }
                if (sval == NULL) {
                    retVal = ERRARGNUM;
                    goto end;
                }
                if (*tmpBuf)
                    printf(lenLim == ON ? "%.*s" :"%*s", atoi(tmpBuf), tmpsval);
                tmpBuf[0] = '\0', lenLim = OFF, arg_num--;
                break;
            case '*':
                ival = va_arg(ap, int);
                sprintf(tmpBuf, "%d", ival);
                goto jump_to_symbol;
                break;
            case '.':
                lenLim = ON;
                goto jump_to_symbol;
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
end:
    free(tmpBuf);
    tmpBuf = NULL;
    va_end(ap);    /* clean up when done */
    return retVal;
}

