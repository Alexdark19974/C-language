#include <stdio.h>
#define MAXLINE 10

int get_line (char charline[], int maxline) 
{
    int c;
    int i = 0;
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
    for (i = 0; from[i] != '\0';)
    {
         to[i] = from[i];
         i++;
    }
    to[i] = '\0';
}
int main(void)
{
    int length; // current line length
    int max = 0; // current max line
    char line[MAXLINE]; // current line input
    char longest[MAXLINE]; // the longest line
    while ((length = get_line(line, MAXLINE)) > 0) // 5
    {
        if (length >= max)
        {
                max = length;
                copy(longest, line);
        }
    }
    if (max > 0 && max > 80)
        {
            printf("\n%d: %s\n", max, longest);
        }
    return 0;
}


