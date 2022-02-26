#include <stdio.h>
#include <stdlib.h>
#define MAXL 1000
#define TAB 8

int get_line (char[], int);
void entab (char[], char[], int, char**);

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
        entab(s_edited, s, argc, argv);
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
void entab (char s_edited[], char s[], int argc, char **argv)
{
    int i = 0;
    int j = 0;
    int b_count = 0;
    int t_count = 0;
    int s_count = 1;
    int parameters = 0;
    int m_columns = atoi(*argv);

    if (argc > 0)
    {
        parameters = 1;
    }

    while (s[j] != '\0')
    {
        if (s[j] == ' ')
        {
            if (parameters && argc > 0 && (s_count % atoi(*argv)))
            {
                b_count++;
                j++;
            }
            else if (parameters && argc > 0 && (s_count % atoi(*argv) == 0))
            {
                t_count++;

                if (m_columns)
                {
                    b_count++;
                    while (b_count)
                    {
                        s_edited[i] = 'b';
                        i++;
                        b_count--;
                    }
                    m_columns = 0;
                    t_count = 0;                
                }
                b_count = 0;
                j++;

                if (argc != 0)
                {
                    argv++;
                    argc--;
                }
                else
                {
                    argc = 0;
                }
            }
            else if (!argc)
            {
                b_count++;
                j++;
            }

            if (!parameters && s_count % TAB)
            { 
                b_count++;
                j++;
            }
            else if (!parameters && (s_count % TAB) == 0)
            {
                t_count++;
                j++;
                b_count = 0;
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
            s_edited[i] = s[j];
            i++; 
            j++;
        }
        s_count++;
    }
    s_edited[i] = '\0';
}