#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#define MAXLINE 1000
#ifdef CASE_1
void standard_scanf();
#elif CASE_2
void standard_sscanf();
int get_line(char *, int);
#else
#define ON  1
#define OFF 0
#define OK  0
enum errwarnCase { ERRNOMEM = -1, WARNARGNUM = -2, ERRNOARG = -3, ERRINVALIDSYM = -4, ERRMISMATCH = -5 };
typedef unsigned int uint;
int min_scanf();
int minscanf(int argNum, char *fmt, ...);
int get_line(char *, int);
void handle_err_warn(int, int);
#endif

main()
{
#ifdef CASE_1
    standard_scanf();
#elif CASE_2
    standard_sscanf();
#else
    min_scanf();
#endif
    exit(EXIT_SUCCESS);
}

#ifdef CASE_1
void standard_scanf()
{
    int day, year, month, retVal;
    char monthname[20];
    retVal = scanf("%d %s %d", &day, monthname, &year);
    printf("retVal = %d, day=%d, month=%s, year=%d; trailing symbol=%d\n", retVal, day, monthname, year, getchar());
}
#elif CASE_2
void standard_sscanf()
{
    int day, month, year, retVal;
    char monthname[20];
    char line[MAXLINE] = {0};

    while (get_line(line, sizeof(line)) > 0) {
        if ((retVal = sscanf(line, "%d %s %d", &day, monthname, &year)) == 3)
            printf(strlen(line) - 1 == '\n' ? "retVal = %d, valid: %s\n" : "retVal = %d, valid: %s", retVal, line);    /* 25 Dec 1988 form */
        else if ((retVal = sscanf(line, "%d/%d/%d", &month, &day, &year)) == 3)
            printf(strlen(line) - 1 == '\n' ? "retVal = %d, valid: %s\n" : "retVal = %d, valid: %s", retVal, line);    /* mm/dd/yy form */
        else
            printf("invalid: %s\n", line);  /* invalid form */
    }
}

int get_line(char *s, int lim)
{
    int i, c = 0;

    for (i = 0; (i < lim) && ((c = getchar()) != EOF) && (c != '\n'); ++i)
        *(s + i) = c;
    if (c == '\n')
        *(s + i) = c, i++;
    *(s + i) = '\0';
    return c == EOF ? EOF : i;
}
#else
int min_scanf()
{
    int argNum = 3, ival = 0, retVal = 0, day = 0, month = 0, year = 0;
    long int lval = 0;
    char sval[MAXLINE] = {0}, monthname[MAXLINE] = {0};

    if ((retVal = minscanf(argNum, "%d/%*d/%d\n", &day, &month, &year)) != OK || retVal < 0)
        handle_err_warn(retVal, argNum);
    if (*sval)
        printf(sval[strlen(sval) - 1] == '\n' ? "retVal=%d, sval=%s" : "retVal=%d, sval=%s\n", retVal, sval);
    else
        printf("retVal=%d, day=%d, month=%d, year=%d\n", retVal, day, month, year);
    return 0;
}

int get_line(char *s, int lim)
{
    int i, c = 0;

    for (i = 0; (i < lim) && ((c = getchar()) != EOF) && (!isspace(c)); ++i)
        *(s + i) = c;
    if (c == '\n')
        *(s + i) = c, i++;
    *(s + i) = '\0';
    return c == EOF ? EOF : i;
}

int minscanf(int argNum, char *fmt, ...)
{
    va_list ap;
    int *ivalp, retVal = OK, i = 0, c = 0;
    long int *lvalp;
    unsigned long int *ulvalp;
    uint *uivalp;
    char *sval, *p, strLimit[MAXLINE] = {0}, isSupressInput = 0;
    float *dvalp;

    va_start(ap, fmt);

    if (argNum <= 0) {
        retVal = ERRNOARG;
        goto end;
    }

    for (p = fmt; *p; p++) {
        if (*p != '%' && *p != '.') {
            if (*(p - 1) != '%') {
                if (isspace(*p)) {
                    getchar();
                    continue;
                }
                if ((c = getchar()) != *p) {
                    retVal = ERRMISMATCH;
                    goto end;
                } else continue;
            }
            else
                retVal = WARNARGNUM;
        }
        if (!argNum)
            continue;
jump_to_sym:
        switch (*++p)
        {
            case 'u':
                if (isSupressInput == ON) {
                    scanf("%*u");
                    isSupressInput = OFF;
                } else {
                    uivalp = va_arg(ap, uint *);
                    scanf("%u", uivalp);
                    argNum--, retVal++;
                }
                break;
            case 'i':
            case 'd':
                if (isSupressInput == ON) {
                    scanf("%*d");
                    isSupressInput = OFF;
                } else {
                    ivalp = va_arg(ap, int *);
                    scanf("%d", ivalp);
                }
                argNum--, retVal++;
                break;
            case 'c':
                ivalp = va_arg(ap, int *);
                scanf("%c", (char *) ivalp);
                argNum--, retVal++;
                break;
            case 'h':
                if (*(p + 1) != 'd' && *(p + 1) != 'u') {
                    retVal = ERRINVALIDSYM;
                    goto end;
                }
                if (*(p + 1) == 'u') {
                    uivalp = va_arg(ap, uint *);
                    scanf("%hu", (unsigned short *)ivalp);
                } else {
                    ivalp = va_arg(ap, int *);
                    scanf("%hd", (short *)ivalp);
                }
                p++, argNum--, retVal++;
            case 'l':
                if (*(p + 1) != 'd' && *(p + 1) != 'u') {
                    retVal = ERRINVALIDSYM;
                    goto end;
                }
                if (*(p + 1) == 'u') {
                    if (isSupressInput == ON) {
                        scanf("%*lu");
                        isSupressInput = OFF;
                    } else {
                        ulvalp = va_arg(ap, unsigned long *);
                        scanf("%lu", ulvalp);
                    }
                } else {
                    if (isSupressInput == ON) {
                        scanf("%*ld");
                        isSupressInput = OFF;
                    } else {
                        lvalp = va_arg(ap, long *);
                        scanf("%ld", lvalp);
                    }
                }
                p++, argNum--, retVal++;
                break;
            case 'g':
            case 'f':
                if (isSupressInput == ON) {
                    scanf("%*f");
                    isSupressInput = OFF;
                } else {
                    dvalp = va_arg(ap, float *);
                    scanf("%f", dvalp);
                }
                argNum++, retVal++;
            case 's':
               sval = va_arg(ap, char *);
               if (isSupressInput == ON) {
                   scanf("%*s");
                   isSupressInput = OFF;
               } else if (*strLimit) {
                   int lim = atoi(strLimit);
                   *strLimit = '\0';
                   if ((lim = get_line(sval, lim)) < 0)
                           goto end;
               } else
                   scanf("%s", sval);
               argNum--, retVal++;
               break;
            case '*': // suppress the input
               isSupressInput = ON;
               goto jump_to_sym;
            default:
               if (isdigit(*p)) {
                   strLimit[i++] = *p++;
                   while (isdigit(*p))
                       strLimit[i++] = *p++;
                   strLimit[i] = '\0', p--;
                   goto jump_to_sym;
               }
               break;
        }
    }
end:
    va_end(ap);
    return retVal;
}

void handle_err_warn(int errWarn, int argNum)
{
    switch (errWarn)
    {
        case ERRINVALIDSYM:
            printf("error: check your format string\n");
            break;
        case WARNARGNUM:
            printf("warning: skipping one of the format specifiers due to number of args is %d\n", argNum);
            break;
        case ERRNOARG:
            printf("warning: number of arguments=%d\n", argNum);
            break;
        case ERRMISMATCH:
            printf("error: input doesn't match format string.\n");
            break;
        case OK:
        default:
            if (errWarn < 0)
                printf("Error of unknown origin. Check the format string and argNum\n");
            break;
    }

}
#endif

