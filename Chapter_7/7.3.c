#include <stdio.h>

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#define ON      1
#define OFF     0
#define OK      0
#define MAXLINE 100
enum errwarnCase { ERRNOMEM = -1, WARNARGNUM = -2, ERRNOARG = -3, ERRINVALIDSYM = -4 };
int minprintf(int, char *, ...);
void handle_err_warn(int, int);
typedef unsigned int uint;

main()
{
    int retVal = OK, argNum = 5;
    printf("standard printf: ");
    printf(":%-*.*s: %u %g\n", 15, 10, "Hello!", 1, 5.7);
    printf("      minprintf: ");
    if ((retVal = minprintf(argNum,":%-*.*s: %u %g PUT HIM DOWN ON THE GROUND!\n", 15, 10, "Hello!", 1, 5.7)) != OK)
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
        case ERRINVALIDSYM:
            printf("error: check your format string\n");
            break;
        case WARNARGNUM:
            printf("warning: skipping one of the format specifiers due to number of args is %d\n", argNum);
            break;
        case ERRNOARG:
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
    int ival, i = 0, lenLim = 0, shift = 0, retVal = OK;
    uint uival;
    double dval;

    va_start(ap, fmt);

    if (arg_num <= 0) {
        va_end(ap);
        retVal = ERRNOARG;
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
            case 'c':
                ival = (char) va_arg(ap, int);
                printf("%c", ival);
                arg_num--;
                break;
            case 'h':
                if (*(p + 1) != 'd') {
                    retVal = ERRINVALIDSYM;
                    goto end;
                }
                ival = (short) va_arg(ap, int);
                printf("%hd", ival);
                p++;
                arg_num--;
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
                for (sval = va_arg(ap, char *), tmpsval = sval; sval != NULL && *sval; sval++) {
                    if (!*tmpBuf)
                        putchar(*sval);
                }
                if (*tmpBuf) {
                    if (shift != OFF && lenLim == ON)
                        printf("%*.*s", shift, atoi(tmpBuf), tmpsval);
                    else
                        printf(lenLim == ON ? "%.*s" : "%*s", atoi(tmpBuf), tmpsval);
                }
                tmpBuf[0] = '\0', lenLim = OFF, shift = OFF, arg_num--;
                break;
            case '*': // replace '*' with a number
                if (shift != OFF)
                    shift = ival;
                if (ival < 0)
                    ival *= va_arg(ap, int);
                else
                    ival = va_arg(ap, int);
                sprintf(tmpBuf, "%d", ival);
                arg_num--;
                goto jump_to_symbol;
                break;
            case '.': // word length delimiter
                if (!isdigit(*(p + 1)) && *(p + 1) != '*') {
                    retVal =  ERRINVALIDSYM;
                    goto end;
                }
                lenLim = ON;
                if (*tmpBuf)
                    shift = ON, i = 0;
                goto jump_to_symbol;
            default:
                if (isdigit(*p) || (*p == '-' && (isdigit(*(p + 1)) || *(p + 1) == '.' || *(p + 1) == '*'))) {
                    if (shift == ON)
                        shift = atoi(tmpBuf);
                    if (*p == '-' && *(p + 1) == '*') {
                        ival = -1;
                        goto jump_to_symbol;
                    }
                    tmpBuf[i++] = *p++;
                    if (*p == '.') {
                        p--;
                        goto jump_to_symbol;
                    }
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

