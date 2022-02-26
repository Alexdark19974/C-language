#include <stdio.h>
#include <stdlib.h>
#define MAXL 1000
#define TAB 8

int get_line (char *, int);
void detab (char *, char *, int, char **);

/* Extend entab and detab to accept the shorthand:
    entab -m +n
to mean tab stops every n columns; starting at column m.
choose convenient size for the default behaviour */

int main (int argc, char *argv[])
{
    char s[MAXL];
    char s_edited[MAXL];
    int len = 0;
    int c = 0;
    int tab_start = 0;
    int next_tab = 0;

    while ((--argc > 0 && (*++argv)[0] == '-') || ((*argv)[0] == '+'))
    {
        while ((c = *++argv[0]))
        {
            switch (c)
            {
                case 'm':
                {
                    if (*(*argv - 1) == '-')
                    {
                        tab_start = 1;
                    }                    
                    break;
                }
                case 'n':
                {
                    if (*(*argv - 1) == '+')
                    {
                        next_tab = 1;
                    } 
                    break;
                }
                default:
                {
                    printf("error: illegal option %c\n", c);
                    return EOF;
                }
            }
        }
    }

    if (!argc || !tab_start || !next_tab)
    {
        printf ("Usage: input -m and +n parameters\n");
        return EOF;
    }

    while ((len = get_line(s, MAXL)) > 0)
    {   
        if (len > 0)
        {
            detab(s_edited, s, argc, argv);
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
        return i;
    }
    i++;
    s[i] = '\0';
    return i;
}
void detab (char s_edited[], char s[], int argc, char **argv)
{
    int parameters = 0;
    int left_over = 0;
    int count = 0;
    int detab = 0;
    int m_columns = atoi(*argv);
    int i = 0;
    int j = 0;

    if (argc > 0)
    {
        parameters = 1;
    }

    while (s[j] != '\0')
    {
        if (parameters && argc > 0 && s[j] == '\t')
        {
            detab = atoi(*argv);

            int res = detab - (count % detab) - left_over;
            left_over = left_over + res;

            if (res == m_columns)
            {
                while (res > 0)
                {
                    s_edited[i] = ' ';
                    i++;
                    res--;
                }
                m_columns = 0;
            }

            while (res > 0)
            {
                s_edited[i] = 'b';
                i++;
                res--;
            }
            j++;

            if (argc != 0 && !m_columns)
            {
                argc--;
                argv++;
            }
            else if (argc <= 0)
            {
                argc = 0;
            }
        }
        else if (!parameters && s[j] == '\t' && argc <= 0)
        {
            int res = TAB - (count % TAB); 

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