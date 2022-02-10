#include <stdio.h>
#define MAXL 1000
#define TAB 8
int get_line (char[], int);
void detab (char[], char[]);
int main (void)
{
    char s[MAXL];
    char s_edited[MAXL];
    int len;
    while ((len = get_line(s, MAXL)) > 0)
    {
        if (len > 0)
        {
            detab(s_edited, s);
            printf("%s", s_edited);   
        }
    }
    return 0;
}
int get_line (char s[], int max)
{
    int c, i = 0;
    for (i = 0; i < MAXL - 2 && (c = getchar()) != EOF && c != '\n'; i++)
    {
        s[i] = c;
    }
    if (c == '\n')
    {
        s[i] = c;
    }
    else if (c == EOF)
    {
        s[i] = '\0';
        puts("");
        return i;
    }
    i++;
    s[i] = '\0';
    return i;
}
void detab (char s_edited[], char s[])
{
    int i = 0;
    int count = 0;
    int j = 0;

    while (s[j] != '\0')
    {
        if (s[j] == '\t')
        {

            int res = TAB - (count % TAB);

            printf("blanks to put are %d\n", res);

            while (res > 0)
            {
                s_edited[i] = 'b';
                i++;
                res--;
            }
            count = 0;
            j++;
        }
        else
        {
            s_edited[i] = s[j];
            i++;
            j++;
            count++;
        }
    }
    s_edited[i] = '\0';
}
