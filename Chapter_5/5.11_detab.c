#include <stdio.h>
#include <stdlib.h>
#define MAXL 1000
#define TAB 8

int get_line (char *, int);
void detab (char *, char *, int, char **);

//detab replaces '\t' symbols with the number of blank spaces that are necessary
//a new program should 
//Modify the programs entab and detab (written as exercises in Chapter 1) to accept a list of tab stops as arguments. Use the default tab settings if there are no arguments.

int main (int argc, char *argv[])
{
    char s[MAXL];
    char s_edited[MAXL];
    int len = 0;
    int base_argc = argc;
    while ((len = get_line(s, MAXL)) > 0)
    {
        if (len > 0)
        {
            detab(s_edited, s, --argc, ++argv);
            printf("%s", s_edited);
            argc = base_argc;
            --argv;
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
            printf ("0) argc is %d\n", argc);

            detab = atoi(*argv);

            int res = detab - (count % detab) - left_over;
            left_over = left_over + res;

            printf("detab is %d\n", detab);

            printf ("2) position is %d\n 3) blank spaces to reach next tab stop is %d\n", count, res);
            
            while (res > 0)
            {
                s_edited[i] = 'b';
                i++;
                res--;
            }
            j++;

            if (argc != 0)
            {
                argc--;
                argv++;
            }
            else if (argc <= 0)
            {
                argc = 0;
            }

            printf("4) position with blanks is %d\n", count);
        }
        else if (!parameters && s[j] == '\t' && argc <= 0)
        {

            int res = TAB - (count % TAB); 

            printf ("9) blank spaces to reach next tab stop is %d\n", res);
            printf("10) position with blanks is %d\n", count);

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
        printf("10) position is %d\n", count);
    }
    printf("5) overall position except \\n and shift is %d\n", count - 2);
    s_edited[i] = '\0';
}