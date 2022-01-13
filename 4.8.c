#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXOP 100

char buf;
int bufp = 0;
int lock = 0;

int getch(void);
void ungetch(int);
void ungets(char[]);


/*
Suppose that there will never be more than one character of pushback. Modify getch and ungetch accordingly.
*/


int main(void)
{
    char string [MAXOP];
    int c = 0;
    int i = 0;
    
    while ((string[i++] = c = getch()) != EOF && c != '\n')
    {
        ;
    }
    string[--i] = '\0';

    ungets(string);

    while((c = getch()) != EOF)
    {
        putchar(c);
        bufp = 0;
    }
    return 0;
}
int getch(void)
{
    return (bufp > 0) ? buf : getchar();
}

void ungetch(int c)
{
    if (bufp > 0 && lock == 0)
    {
        printf("ungetch: too many characters\n");
        lock = 1;
    }
    else if (lock == 0)
    {
        buf = c;
        bufp++;
    }
}

void ungets(char s[])
{
    int length = strlen(s);
    int i = 0;
    while (i != length)
    {
        ungetch(s[i++]);
    }    
}