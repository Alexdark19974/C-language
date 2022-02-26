#include <stdio.h>
#define MAXL 1000
#define TAB 8

int get_line (char[], int);
void entab (char[], char[]);

int main (void)
{
    char s[MAXL], s_edited[MAXL];
    int len;
    while ((len = get_line(s, MAXL)) > 0)
    {
        entab(s_edited, s);
        printf("%s", s_edited);   
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
void entab (char s_edited[], char s[])
{
    int i = 0;
    int j = 0;
    int b_count = 0;
    int t_count = 0;
    int s_count = 1;

    while (s[j] != '\0')
    {
        if (s[j] == ' ')
        {
            if (s_count % TAB)
            {
                b_count++;
                j++;
            }
            else
            {
                t_count++;
                j++;
                b_count = 0;
                printf("t_count is %d\n", t_count);
            }
        }
        else if (s[j] != ' ')
        {
            if (t_count)
            {
                while (t_count > 0)
                {
                    s_edited[i] = 't';
                    i++;
                    t_count--;
                }
            }
            if (b_count)
            {
                while (b_count)
                {
                    s_edited[i] = 'b';
                    i++;
                    b_count--;
                }
            }
            if (s[j] == '\t')
            {
                s_edited[i] = s[j];
                s_count = s_count + (TAB - (s_count % TAB)); 
            }
            else
            {
                s_edited[i] = s[j];
            }
            i++;
            j++;
            
        }
        s_count++;
    }
    s_edited[i] = '\0';
}
