#include <stdio.h>
#define MAXLINE 1000
#define LIMIT 80
int get_line (char charline[], int maxline) 
{
    int i = 0, j = 0, c = 0;

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
        i++;
    }
    return i;
}
void copy(char to[], char from[])
{
    int i = 0;
    while (from[i] != '\n')
    {            
        to[i] = from[i];
        i++;
    }
    to[i] = '\n';
}

int main(void)
{
    int length = 0, current_line = 0;
    char line[MAXLINE];
    char over_80[MAXLINE];

    while ((length = get_line(line, MAXLINE)) > 0)
    {
        if (length > LIMIT)
        {
            copy(over_80 + current_line, line);
            current_line =  current_line + length;
        }
    }
    if (current_line > LIMIT)
        {
            printf("%s\n",over_80);
        }
    return 0;
}
