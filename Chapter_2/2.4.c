#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 1000

void get_line (char[], int);
void squeeze (char[], char[]);

int main(void)
{
    char string2[MAX + 1];
    char string[MAX + 1];
    get_line(string, MAX);
    get_line(string2, MAX);
    squeeze(string, string2);
    printf("%s\n", string);
    return 0;
}

void squeeze (char s[], char s1[])
{
    int i, j, n ;

    for (int n = 0; s1[n] != '\0'; n++)
    {
        for (i = j = 0; s[i] != '\0'; i++)
        {
            if (s[i] != s1[n])
            {
                s[j] = s[i];
                j++;
            }
        }
        s[j] = '\0';
    }
}

void get_line (char s[], int max)
{
    int c, i = 0;
    for (i = 0; i < MAX - 1 && (c = getchar()) != EOF && c != '\n'; i++)
    {
        if (c >= 'A' && c <= 'Z')
        {
            c = tolower(c);
        }
        s[i] = c;
    }
    if (c == '\n')
        {
            s[i] = '\0';
            ++i;
        }

        s[i] = '\0';

    return;
}

