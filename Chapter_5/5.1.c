#include <stdio.h>
#include <ctype.h>
#define SIZE 128
#define BUFSIZE 256
int getch(void);
void ungetch(int);
int n, array[SIZE], getint(int *pn);
int bufp = 0;
char buf[BUFSIZE];

main(void)
{
    int i;
    for (n = 0; n < SIZE && getint(&array[n]) != EOF; n++)
        ;
    printf("Array of integers = ");
    for (i = 0; i < n; i++)
        printf("%d ", array[i]);

    return 0;
}

/* getint:  get next integer from input into *pn */
int getint (int *pn)
{
    int c, sign = 0;

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
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;
    if (c != EOF)
        ungetch(c);
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
