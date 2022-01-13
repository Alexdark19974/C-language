#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXOP 100
#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void);
void ungetch(int);
void ungets(char[]);

/*
Write a routine ungets(s) that will push back an entire string onto the input. Should ungets know about buf and bufp, or should it just use ungetch?

Suppose that there will never be more than one character of pushback. Modify getch and ungetch accordingly.
*/


int main(void)
{
    char string [MAXOP];
    int c = 0;
    int i = 0;
    while (c != EOF)
    {
        while ((string[i++] = c = getch()) != EOF && c != '\n')
        {
            ;
        }
        string[i] = '\0';
        i = 0;
        ungets(string);
        
        while ((c = getch()) != '\0' && c != EOF)
        {
            putchar(c);
        }
    }    
    return 0;
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

void ungets(char s[])
{
    int i = strlen(s);    
    while (i >= 0)
    {
        ungetch(s[i--]);
    }    
}