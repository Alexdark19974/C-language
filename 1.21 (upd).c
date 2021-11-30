#include <stdio.h>
#define MAXL 1000
#define TAB 8
/* Write a program entab that replaces strings of blanks with the minimum number of tabs and blanks to achieve the same spacing. 
  Use the same stops as for detab.
 When either a tab or a single blank would suffice to reach a tab stop, which should be given preference? */
int get_line (char[], int);
void entab (char[], char[]);
int main (void)
{
    char s[MAXL];
    char s_edited[MAXL];
    int len;
    while ((len = get_line(s, MAXL)) > 0)
    {
        if (len > 0)
        {
            entab(s_edited, s);
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
void entab (char s_edited[], char s[])
{
    int i = 0;
    int s_count = 1;
    int b_count = 0;
    int t_count = 0;
    int j = 0;
    while (s[j] != '\0')
    {
        if (s[j] == ' ')
        {

            if (s_count % TAB != 0)
            {
                b_count++;
                j++;
            }
            else
            {
                t_count++;
                b_count = 0;
                j++;
                 s_count = 1;

            }
        }
        else if (s[j] != ' ')
        {
            if (t_count > 0)
            {
                while (t_count > 0)
                {
                    s_edited[i] = '\t';
                    i++;
                    t_count--;
                }
            }
            if (b_count > 0)
            {
                while (b_count > 0)
                {
                    s_edited[i] = ' ';
                    i++;
                    b_count--;
                }
            }
                s_edited[i] = s[j];
                i++;
                j++;
        }
        s_count++;
    }
    s_edited[i] = '\0';
}