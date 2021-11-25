#include <stdio.h>
#define MAXLINE 1000

int get_line (char charline[], int maxline) 
{
    int c;
    int i;
    for (i = 0; i < maxline - 1 && (c = getchar()) != EOF && c!= '\n'; i++)
    {
        charline[i] = c;
    }
    if (c == '\n')
    {
        charline[i] = c;
        i++;
    }

    charline[i] = '\0';
    return i;
}
void copy(char to[], char from[])
{
    int i = 0;
    while ((to[i] = from[i]) != '\0')
    {
        i++;
    }
}
int main(void)
{
    int length; // current line length
    int max = 0; // current max line
    char line[MAXLINE]; // current line input
    char longest[MAXLINE]; // the longest line

    while ((length = get_line(line, MAXLINE)) > 0)
    {
        if (length > max && length > 80)
        {
            max = length;
            copy(longest, line);
        }
    }
    if (max > 0)
        {
            printf("%s", longest);
        }
    return 0;
}


