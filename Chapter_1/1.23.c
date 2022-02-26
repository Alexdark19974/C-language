#include <stdio.h>
#define LLIMIT 1000
int get_line (char[], int);
void remove_comments(char[], char[], int);
/* Write a program to remove all comments from a C program. Don’t forget to handle quoted strings and character constants properly. C comments don’t nest. */

int main (void)
{
    char string[LLIMIT];
    char string_removed_comments[LLIMIT];
    int length = 0;
    int quote = 0;
    int unquote = 0;

    while ((length = get_line(string, LLIMIT)) > 0)
    {
        remove_comments(string_removed_comments, string, length);
        printf("%s", string_removed_comments);
    }
    return 0;
}

int get_line(char string[], int maxs)
{
    int i = 0;
    int c;
    int tab_count = 0;

    while (i < maxs - 2 && (c = getchar()) != EOF && c != '\n')
    {
            string[i] = c;
            i++;
    }

    if (c == '\n')
    {
        string[i] = c;
    }
    if (c == EOF)
    {
        string[i] = '\0';
        return i;
    }

    i++;
    string[i] = '\0';

    return i;    
}

void remove_comments (char to[], char from[], int length)
{
    int i = 0;
    int j = 0;
    int s = length;
    int commentIN = 0;
    int commentOUT = 0;
    int left = 0;
    int right = 0;
    int quote = 0;
    int unquote = 0;

    while (from[i] != '\0')
    {
        if (from[i] == '\"')
        {
            quote++;
            for (int i = s; i > 0; i--)
            {
                if (from[i] == '\"')
                {
                    quote++;
                    break;
                }
            }
        }
        if (from[i] == '/' && from[i + 1] == '/' && quote != 2)
        {
            while (from[i] != '\0')
            {
                i++;
            }
        }
        
        else if (from[i] == '/' && from[i + 1] == '*' && from[i + 2] != '/' && quote != 2)
        {
                commentIN++;
                left = i;

            for (int i = s; i >= 0; i--)
            {
                if (from[i - 2] != '/' && from[i - 1] == '*' && from[i] == '/')
                {
                    commentOUT++;
                    right = i;
                    break;
                }
            }
        }
        if (commentIN == 1 && commentOUT == 1)
        {
            while (left <= right)
            {
                i++;
                left++;
            }
        }
        to[j] = from[i];
        j++;
        i++;
}
    to[j] = '\0';
}