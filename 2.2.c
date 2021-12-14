#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

void get_line (char[], int);

int main (void)
{
    char s[MAXLINE];
    get_line(s, MAXLINE);

    return 0;
}

void get_line (char s[], int m)
{
    int i = 0; 
    int c;
    int length;
    for (i = 0; i < m - 1; i++)
    {
        if ((c = getchar()) != '\n')
        {
            if (c != EOF)
            {
                s[i] = c;
            }

            }
            else
            {
                s[i] = '\0';
                printf ("%d %d is the length of the string\n", i, length = strlen(s));
                return;
            }
    }
}