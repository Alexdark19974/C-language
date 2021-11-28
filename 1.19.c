	
//Write a function reverse(s) that reverses the character string s . Use it to write a program that reverses its input a line at a time.

#include <stdio.h>
#define MAXL 1000
void reverse(char[], int);
int get_line(char[], int);
int main (void)
{
    char s[MAXL];
    int length = 0;
    while ((length = get_line(s, MAXL)) > 0)
    {
        if (length > 0)
        {
            reverse(s, length);
            printf("%s", s);
        }
    }
    return 0;
}
void reverse (char s[], int length)
{
    char temp;

    for (int i = 0; i < length/2; i++)
    {
        temp = s[i];
        s[i] = s[length - 2 - i];
        s[length - 2 - i] = temp;
    }

}
int get_line(char s[], int MAXLINE)
{
    int c;
    int i = 0;
    for (i = 0; i < MAXLINE - 2 && (c = getchar()) != EOF && c != '\n';)
    {
        s[i] = c;
        i++;
    }
    if (c == '\n')
    {
        s[i] = c;
        i++;
        s[i] = '\0';    
    }
    else if (c == EOF)
    {
        s[i] = '\0';
        puts("");
    }
    return i;
}
