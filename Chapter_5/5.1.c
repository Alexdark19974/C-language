#include <stdio.h>
#include <ctype.h>
#define SIZE 100
#define MAXVAL 100
#define BUFSIZE 100

/*
As written, getint treats a + or - not followed by a digit as a valid representation of zero. Fix it to push such a character back on the input.
*/

int sp = 0;
char buf[BUFSIZE];
int bufp = 0;

int getch(void);
void ungetch(int);
int getint (int *);

int main(void)
{
    int n = 0;
    int array[SIZE] = {0};
    int res = 0;

    for (n = 0; n < SIZE && (res = getint(&array[n++])) != EOF && res != 0;)
    {
        printf("the value of getint is %d\n", array[n - 1]);
    }
    
    if (!res == 0)
    {
        printf("invalid number. Aborted.\n");
        return 0;
    }

    puts("");

    printf("getint contains : ");

    for (int i = 0; i != BUFSIZE; i++)
    {
        printf("%d ", array[i]);
    }

    printf("\nbuffer for input: ");
    for (int i = 0; i != BUFSIZE; i++)
    {
        printf("%c ", buf[i]);
    }
    return 0;
}

int getint(int *pn)
{
    int c = 0;
    int sign = 0;
    int symbol = 0;

    while (isspace(c = getch()))
    {
        ;     
    }

    if (!isdigit(c) && c != EOF && c != '+' && c != '-')
    {
        ungetch(c);
        return 0;
    }

    sign = (c == '-') ? -1 : 1;

    if (c == '+' || c == '-')
    {
        symbol = c;
        c = getch();
    }
    
    if (!isdigit(c))
    {
         ungetch(symbol);

        if (c != EOF)
        {
            ungetch(c);
        }
        return symbol;
    }
    

    for (*pn = 0; isdigit(c); c = getch())
    {
        *pn = (10 * *pn) + (c - '0');
    }

    *pn *= sign;

    if (c != EOF)
    {
        ungetch(c);
    }
    return c;
}

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
    {
        printf("ungetch: too many characters\n");
    }
    else
    {
        buf[bufp++] = c;   
    }
}
