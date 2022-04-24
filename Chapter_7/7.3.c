#include <stdio.h>
#include <stdarg.h>

void minprintf(char *fmt, ...);

main()
{
	int a = 123;
	int b = 124;
	int c = 153;
	int d = 1354253;
	char *string = "Hello, World!";
    minprintf("%d %d %d %d %s\n", a, b, c, d, string);
    return 0;
}

/* minprintf: ограниченная версия printf
   со списком аргументов переменной длины */

void minprintf(char *fmt, ...)
{
    va_list ap; /* указатель на безымянные аргументы */

    char *p, *sval;
    int ival;
    double dval;

    va_start(ap, fmt); /* установить ap на 1-й аргумент без имени */
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }
        switch(*++p) {
        case 'd':
            ival = va_arg(ap, int);
            printf("%d", ival);
            break;
        case 'f':
            dval = va_arg(ap, double);
            printf("%f", dval);
            break;
        case 's':
            for (sval = va_arg(ap, char *); *sval; sval++)
                putchar(*sval);
            break;
        default:
            putchar(*sval);
            break;
        }
    }
    va_end(ap); /* заврешающие операции  */
}
