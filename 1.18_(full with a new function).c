#include <stdio.h>
#define MAXLINE 1000
#define LIMIT 0
int get_line(char[], int);
void removal(char[], char[]);

int main(void)
{
    int length = 0;
    char line[MAXLINE];
    char edited[MAXLINE];

    while ((length = get_line(line, MAXLINE)) > 0)
    {
        if (length > LIMIT)
        {
            removal(edited, line);
            printf("%s\n", edited);
        }
    }
    return 0;
}

int get_line(char charline[], int maxline) 
{
    int i = 0, c = 0;

    for (i = 0; i < maxline - 2 && (c = getchar()) != EOF && c!= '\n';)
    {
        charline[i] = c;
        i++;
    }
    if (c == '\n')
    {
        charline[i] = c;
        i++;
        charline[i] = '\0';
    }
    if(c == EOF)
    {
        charline[i] = '\0';
        puts("");
    }
    return i;
}

void removal(char to[], char from[])
{
    int i = 0;
    int j = 0;
    while (from[i] != '\n' && from[i] != '\0')
    {
        i++;
        i--;
        if (from[i] == ' ' && from[i + 1] == ' ')
        {
            to[j] = ' ';
            i++;
        }
        else if (from[i] == '\t' && from[i + 1] == '\t')
        {
            to[j] = ' ';
            i++;
        }
        else if (from[i] == '\t')
        {
            to[j] = ' ';
            j++;
            i++;
        }
        else
        {
            to[j] = from[i];
            i++;
            j++;
        }    
    }
    to[j] = '\n';
    to[j++] = '\0';
}