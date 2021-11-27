#include <stdio.h>
#define MAXLINE 1000
#define LIMIT 0
void get_line(char[], int);

int main(void)
{
    int length = 0;
    char line[MAXLINE];
    char edited[MAXLINE];

    while (length == 0)
    {
        get_line(line, MAXLINE);
        
        if (line[0] == '\n')
        {
            line[0] = '\0';
        }
    }
    return 0;
}
void get_line(char charline[], int maxline) 
{
    int i = 0, c = 0;

    for (i = 0; i < maxline - 2 && (c = getchar()) != EOF && c!= '\n';)
    {
        if (c == '\t')
        {
            if (c == '\t' && charline[i - 1] == ' ' || c == '\t')
            {
                continue;
            }
            else
            {
                charline[i] = ' ';
                i++;
            }    
        }
        else if(charline[i - 1] == ' ' && c == ' ' ||
                charline[i - 1] == ' ' && charline[i] == '\t' || 
                charline[i - 1] == '\t'&& charline[i] == ' ')
        {
            continue;
        }
        else
        {
            charline[i] = c;
            i++;
        }
    }
    if (c == EOF)
    {
        charline[i] = '\0';
        printf("\n%s\n", charline);
        return 0;
    }
    else if (c == '\n')
    {
        charline[i] = c;
        i++;
        charline[i] = '\0';
        printf("%s\n", charline);
    }
}