#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

int get_line(char[], int);
int strindex(char[], char[]);
char pattern[] = "ould";

/*Write the function strrindex(s,t) , which returns the position of the rightmost occurrence of t in s , or -1 if there is none.*/

int main(void)
{
    char line[MAXLINE];
    int index = 0;

    while (get_line(line, MAXLINE) > 0)
    {
        if ((index = strindex(line, pattern)) >= 0)
        {
            printf("%d\n", index);
        }
    }
    return 0;
}

int get_line(char charline[], int maxline) 
{
    int i = 0, c = 0;

    for (i = 0; --maxline > 0 && (c = getchar()) != EOF && c!= '\n';)
    {
        charline[i++] = c;
    }
    if (c == '\n')
    {
        charline[i++] = c;
        charline[i] = '\0';
    }
    if (c == EOF)
    {
        charline[i] = '\0';
        puts("");
    }
    return i;
}


int strindex (char s[], char t[])
{
    int i = 0;
    int k = 0;
    int j = 0;

    for (i = strlen(s) - 2; i >= 0; i--)
    {
        for (j = i, k = strlen(t) - 1; k >= 0 && s[j] == t[k]; j--, k--)
        {
            ;
            if (!k)
            {
                return j;
            }
        }
    }

    return -1;
}