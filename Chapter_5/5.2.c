#include <stdio.h>
#include <ctype.h>
#define SIZE 128
#define BUFSIZE 256
int getch(void);
void ungetch(int);
int n, getfloat(float *pn);
float array[SIZE];
int bufp = 0;
char buf[BUFSIZE];

main(void)
{
    int i;
    for (n = 0; n < SIZE && getfloat(&array[n]) != EOF; n++)
        ;
    printf("Array of floats = ");
    for (i = 0; i < n; i++)
        printf("%f ", array[i]);

    return 0;
}

/* getfloat:  get next float from input into *pn */
int getfloat(float *pn)
{
    int c, divisor = 0, sign = 0;
    static int floating_point = 0;
    while (isspace(c = getch()))    /* skip white space */
        ;
    if ((c == '-' || c == '+') && (sign = c) && !isdigit(c = getch())) {
        ungetch(c);
        ungetch(sign);
        return 0;
    }
    else {
        ungetch(c);
        if (!sign)
            c = '+';
        else
            c = sign;
    }
    /*
     * 
     * These three following lines down below are interesting. 
     * If we enter a non-digit value, say, 'a', 
     * it will be ungetched and getched untill n == SIZE, 
     * upon which the program is done.
     * */
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);    /* it's not a number */
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-')
        c = getch();

    for (*pn = 0; isdigit(c) || c == '.'; c = getch()) {
        if (!floating_point && c == '.') {
            floating_point = c;
            divisor = 1;
            continue;
        }
        if (floating_point && !isdigit(c)) {
            *pn = 0;
            ungetch(c);
            ungetch(floating_point);
            return 0;
        }
        *pn = 10 * *pn + (c - '0');
        divisor*=10;
    }
    *pn *= sign;
    *pn/=divisor;
    if (c != EOF)
        ungetch(c);
    floating_point = 0;
    return c;
}

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
