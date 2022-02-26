#include <stdio.h>
#define MAXLINE 5

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
    int max = 0; // current max line
    int c; //symbol input
    char line[MAXLINE]; // current line input
    char longest[MAXLINE]; // the longest line
    while ((length = get_line(line, MAXLINE)) > 0) // 5
    {
        if (length >= max)
        {
            if (line[length - 1] != '\n' && line[length - 1] != EOF)
            {
                while((c = getchar()) != EOF && c != '\n')
                {
                    length++;
                }
                max = length;
                copy(longest, line);
            }
            else if (line[length  - 1] == '\n')
            {
                max = length;
                copy(longest, line);
            }
        }
    }
    if (max > 0)
        {
            printf("\n%d: %s", max, longest);
        }
    return 0;
}


