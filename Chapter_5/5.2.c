#include <stdio.h>
#include <ctype.h>
#define SIZE 100
#define MAXVAL 100
#define BUFSIZE 100

/*Write getfloat , the floating-point analog of getint . What type does getfloat return as its function value?*/

int sp = 0;
char buf[BUFSIZE];
int bufp = 0;

int getch(void);
void ungetch(int);
int getfloat (float *);

int main(void)
{
    int n = 0;
    float array[SIZE] = {0.0};
    int res = 0;

    for (n = 0; n < SIZE && (res = getfloat(&array[n++])) != EOF && res != 0;)
    {
        printf("the value of getint is %f\n", array[n - 1]);
    }
    if (!res == 0)
    {
        printf("invalid number. Aborted.\n");
        return 0;
    }
    puts("");

    printf("floatint contains : ");

    for (int i = 0, count = 0; i != BUFSIZE; i++)
    {
        printf("%d) %.1lf; ", ++count, array[i]);
    }

    printf("\nbuffer for input: ");
    for (int i = 0; i != BUFSIZE; i++)
    {
        printf("%c ", buf[i]);
    }
    return 0;
}

int getfloat(float *pn)
{
    int c = 0;
    float sign = 0;
    int symbol = 0;
    float power = 1.0;

    while (isspace(c = getch()))
    {
        ;     
    }

    if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.')
    {
        ungetch(c);
        return 0;
    }

    sign = (c == '-') ? -1.0 : 1.0;

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
    
    for (*pn = 0.0; isdigit(c); c = getch())
    {
        *pn = 10.0 * *pn + (c - '0');
    }

    if (c == '.')
    {
        c = getch();
    }

    for (power = 1.0; isdigit(c); c = getch())
    {
        *pn = 10.0 * *pn + (c - '0');
        power *= 10.0; 
    }

    *pn = (sign * (*pn / power));

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


/*Write getfloat , the floating-point analog of getint . What type does getfloat return as its function value?*/