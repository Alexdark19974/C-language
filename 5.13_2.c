#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXL 50
#define ALLOCSIZE 10000
#define DEFAULT 10

/*Write the program tail, which prints the last n lines of its input. By default, n is 10, say, but it can be changed by an optional argument, so that

  tail -n

prints the last n lines. The program should behave rationally no matter how unreasonable the input or the value of n. Write the program so it makes the best use of available storage; lines should be stored as in the sorting program of Section 5.6, not in a two-dimensional array of fixed size.*/

char *alloc(int );
void afree(char *); 
int get_line (char[MAXL], char **, int);
void tail (char**, int, char **);

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;
static char *string_ptr[MAXL];

int main (int argc, char *argv[])
{
    char s[MAXL];
    int len = 0;
    int c = 0;
    int number = 0;
    char *ptr = NULL;
    int n_lines = 0;

    while ((--argc > 0 && (*++argv)[0] == '-'))
    {
        while ((c = *++argv[0]))
        {
            switch (c)
            {
                case 'n':
                {
                    if (*(*argv - 1) == '-')
                    {
                        number = 1;
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

    if (!argc || !number)
    {
        printf ("Usage: input -n parameters\n");
        return EOF;
    }

    while ((len = get_line(s, string_ptr, MAXL)) > 0)
    {
        if (n_lines >= MAXL || ((ptr = alloc(len)) == NULL))
        {
            return EOF;
        }
        else
        {
            if (s[0] == '\n')
            {
                s[0] = '\0';
                break;
            }

            s[len - 1] = '\0';
            strcpy(ptr, s);
            string_ptr[n_lines] = ptr;
            n_lines++;
        }
    }
    
    tail (string_ptr, n_lines, argv);

    afree(*string_ptr);

    return 0;
}
int get_line (char s[MAXL], char **string_ptr, int max)
{
    int c = 0; 
    int i = 0;
    int s_count = 0;

    for (i = 0; i < MAXL - 1 && (c = getchar()) != EOF && c != '\n'; i++)
    {
        s[i] = c;
        s_count++;
    }

    if (c == '\n')
        {
            s[i] = '\n';
            i++;
            s_count++;
        }
    if (c == EOF)
    {
        s[i] = '\0';
        s_count++;
    }
    return s_count;           
}
void tail (char **string_ptr, int n_lines, char **argv)
{
    int i = 0;

    puts("\n----tail is");

    if (!atoi(*argv))
    {
        printf ("default: 10.;\n");

        if (n_lines < DEFAULT)
        {
            printf("the number of lines is less than required to entail.\n");
            return;
        }
        else
        {
            i = DEFAULT;

            for (; i > 0; i--, n_lines--)
            {
                printf("%s\n", *(string_ptr + (n_lines - 1)));
            }    
        }
    }
    else
    {
        i = atoi(*argv);

        for(; i > 0; n_lines--, i--)
        {
            printf("%s\n", *(string_ptr + (n_lines - 1)));
        }
    }
}

char *alloc(int n)
{
    if (allocbuf + ALLOCSIZE - allocp >= n)
    {
        allocp += n;
        return allocp - n; 
    }
    else
    {
        return 0;
    }
}

void afree(char *p)
{
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
    {
        allocp = p;
    }
}