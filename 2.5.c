#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 1000

//K&R 2.5 asks: Write the function any(s1,s2), which returns the first location in the string s1 where any character from the string s2 occurs, or -1 if s1 contains no characters from s2. (The standard library function strpbrk does the same job but returns a pointer to the location.)

void get_line(char[], int);
int any(char[], char[], int[]);

int main(void)
{
    char string2[MAX + 1];
    char string[MAX + 1];
    int string3[MAX + 1] = {0};
    get_line(string, MAX);
    get_line(string2, MAX);
    int res = any(string, string2, string3);

    if (res == -1)
    {
        printf("-1\n");
    }
    else
    {
        for (int i = 0; i < res; i++)
        {
            printf("the first match in string1 is index %d\n", string3[i]);
        }
    }
    return 0;
}

int any(char s[], char s1[], int s3[])
{
    int i, n, l = 0;
    int flag_of_encapsulation = 0;
    int mark_of_absence_of_symbols = 0;

    for (n = 0; s1[n] != '\0'; n++)
    {
        for (i = 0; s[i] != '\0'; i++)
        {
            if (s[i] == s1[n] && flag_of_encapsulation == 0)
            {
                flag_of_encapsulation = 1;
                mark_of_absence_of_symbols = 1;
                s3[l] = i;
                ++l;
            }
        }
            flag_of_encapsulation = 0;
    }
    if (mark_of_absence_of_symbols == 0)
    {
        return -1;
    }
    else
    {
        return l;
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
}