#include <stdio.h>
#define MAXLINE 1000

int get_line (char charline[], int maxline) 
{
    int c;
    int i = 0; // over symbol count
    int j = 0;
    for (j = 0; (c = getchar()) != EOF && c!= '\n';)
    {
        if (j < maxline - 2)
        {
            charline[i] = c;
            j++;
            i++;
        }
        else
        {
            i++;
        }
    }
    if (c == '\n')
    {
        charline[j] = c;
        j++;
        i++;
    }
    charline[j] = '\0';

    return i;
}
void copy(char to[], char from[])
{
    int i = 0;
    while (from[i] != '\0')
    {
         to[i] = from[i];
         i++;
    }
    to[i] = '\0';
}
int main(void)
{
    int length; // current line length
    char line[MAXLINE]; // current line input
    char over_80[MAXLINE]; // line over 80

    while ((length = get_line(line, MAXLINE)) > 0)
    {
        if (length > 80)
        {
            copy(over_80, line);
        }
        else 
        {
            continue;
        }
    }
     printf("\n%s\n",over_80);
    return 0;
}


