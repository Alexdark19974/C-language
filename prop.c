#include <stdio.h>

#define MAXLINE 5

int getlin(char s[], int lim)
{
    int c, i;
    for (i = 0;(c = getchar()) != EOF && c!='\n'; ++i)
    {
        if (i < lim - 1)
        {
            s[i] = c;
        }
    }
 
    if (i < lim-1)
    {
        s[i] = '\0';
    }
    else
    {
        s[lim-1] = '\0';
    } 

    if (c == EOF && i == 0)
    {
        return -1;
    }

        return i;
}

void copy(char to[], char from[])
{
    int i = 0;
    while ((to[i] = from[i]) != '\0')
    {
        ++i;
    }
}

int main(void)
{
    int len;       /* actual line length */
    int max = 0;           /* max. length up to now. */
    char line[MAXLINE];/* actual line read */
    char longest[MAXLINE]; /* max. line stored here */

    while ((len = getlin(line, MAXLINE)) >= 0)

        if (len > max) 
        {
            max = len;
            copy(longest, line);
        }
        if (max > 0)
        {
            printf("\n%d %s\n", max, longest);
            return 0;
        }
}