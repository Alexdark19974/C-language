#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAXLINES 5000
#define ALLOCSIZE 1000
#define MAXLEN 1000


static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;
char *lineptr[MAXLINES];
char len = 0;

int readlines (char *[], int, int, int);
void writelines (char *[], int);
void q_sort (void *[], int, int, int (*) (const void *, const void *, int, int), int, int, int);
int numcmp (const char *, const char *, int, int);
int strcomp (const char *, const char *, int, int);
void substring (char *, const char *, int, int);
int get_line (char *, int, int *, int, int);
char *alloc(int);

/*
5.14
Modify the sort program to handle a -r flag, which indicates sorting in reverse (decreasing) order. Be sure that -r works with -n.
*/

/*
5.15
add the option -f to fold upper and lower case together, so that case distinctions are not made during sorting; for example, a and A compare equal.
*/

/*
5.16
Add the -d ("directory order") option, which makes comparisons only on letters, numbers and blanks. Make sure it works in conjunction with -f .
*/

/*
5.17
Add a field-handling capability, so sorting may be done on fields within lines, each field sorted according to an independent set of options. (The index for this book was sorted with -df for the index category and -n for the page numbers.)
*/

int main (int argc, char *argv[])
{
    int c = 0;
    int nlines = 0;
    int numeric = 0;
    int reverse = 0;
    int f_ = 0;
    int d_ = 0;
    int field_1 = -1;
    int field_2 = -1;

    while (argc > 1 && (*++argv)[0] == '-')
    {
        argc--;

        while ((c = *++argv[0]))
        {
            switch (c)
            {
                case 'd':
                {
                    d_ = 1;
                    break;
                }
                case 'f' :
                {
                    f_ = 1;
                    break;            
                }
                case 'n':
                {
                    numeric = 1;
                    break;
                }
                case 'r':
                {
                    reverse = 1; 
                    break;
                }
                default:
                {
                    printf ("error: unknown command\n");
                    return EOF;
                }
            }
        }
    }

    if (argc > 1 && isdigit(*argv[0]))
    {
        field_1 = atoi(*argv);
        argv++;
        argc--;
    }
    if (argc > 1 && isdigit (*argv[0]))
    {
        field_2 = atoi(*argv);
        argc--;
        argv++;
    }

    if (field_1 < 0 || field_1 > field_2 || field_2 < 0)
    {
        printf ("error: field_1 or field_2 can't be less than 0 or more than field_2\n");
        printf("pattern: flags [1] [3]\n");
        return EOF;
    }

    if ((nlines = readlines (lineptr, MAXLINES, f_, d_)) >= 0)
    {
        q_sort ((void **) lineptr, 0, nlines - 1, (int (*) (const void *, const void *, int, int)) (numeric ? numcmp : strcomp), reverse, field_1, field_2);
        writelines (lineptr, nlines);
        return 0;
    }
    else
    {
        printf("error: input too big to sort\n");
        return 1;
    }
}

void q_sort (void *v[], int left, int right, int (*comp) (const void *, const void *, int, int), int reverse, int field_1, int field_2)
{
    int i = 0;
    int last = 0;
    void swap (void *[], int i, int j);

    if (left >= right)
    {
        return;
    }

    swap (v, left, ((left + right) / 2));

    last = left;
    
    for (i = left + 1; i <= right; i++)
    {
        if (!reverse)
        {
            if ((*comp)(v[i], v[left], field_1, field_2) < 0)
            {
                swap(v, ++last, i);
            }    
        }
        else
        {
            if ((*comp)(v[i], v[left], field_1, field_2) > 0)
            {
                swap(v, ++last, i);
            }
        }   
    }
    
    swap (v, left, last);
  
    q_sort(v, left, last - 1, comp, reverse, field_1, field_2);
    q_sort(v, last + 1, right, comp, reverse, field_1, field_2); 
}

void writelines (char *lineptr[], int nlines)
{
    while (nlines-- > 0)
    {
        printf("%s\n", *lineptr++);
    }
}

int readlines (char *lineptr[], int maxlines, int f, int dir)
{
    char line[MAXLEN];
    int nlines = 0;
    char *p = NULL;
    int mark = 0;
    int f_ = f;
    int d_ = dir;

    while ((len = get_line(line, MAXLEN, &mark, f_, d_)) > 0)
    {
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
        {
            return -1;
        }
        else
        {
            if (line[0] == '\n')
            {
                line[0] = '\0';
                break;
            }

            if (!mark)
            {
                line[len - 1] = '\0';
                strcpy(p, line);
                lineptr[nlines] = p;
                nlines++;
            }
            else
            {
                strcpy(p, line);
                lineptr[nlines] = p;
                nlines++;
                break;
            }
        }
    }
    return nlines;
}

int get_line (char s[MAXLEN], int max, int *mark, int f, int d_)
{
    int c = 0; 
    int i = 0;
    int s_count = 0;

    for (i = 0; i < MAXLEN - 1 && (c = getchar()) != EOF && c != '\n'; i++)
    {
        if (d_)
        {
            if (isalnum(c) || isspace(c))
            {
                if (f)
                {
                    s[i] = tolower(c);
                    s_count++;        
                }
                else
                {
                    s[i] = c;
                    s_count++;
                }
            }
            else
            {
                i--;
            }    
            continue;
        }
        if (f && !d_)
        {
            s[i] = tolower(c);
            s_count++;
        }
        else
        {
            s[i] = c;
            s_count++;
        }
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
        *mark = 1;
    }
    return s_count;           
}

int strcomp (const char *s1, const char *s2, int field_1, int field_2)
{
    char sub_string_1[MAXLINES];
    char sub_string_2[MAXLINES];
    int len_1 = strlen(s1);
    int len_2 = strlen(s2);

    if (len_2 < field_2 || len_1 < field_2)
    {
        printf ("error: pos_2 exceeds the string\n");
        exit(0);
    }

    if ((field_1 && field_2) >= 0)
    {
        substring(sub_string_1, s1, field_1, field_2);
        substring(sub_string_2, s2, field_1, field_2);

        while (*sub_string_1 == *sub_string_2)
        {
            if (*sub_string_1 == '\0')
            {
                return 0;
            }

        }
        return *sub_string_1 - *sub_string_2;
    }
    else
    {
        while (*s1++ == *s2++)
        {
            if (*s1 == '\0')
            {
                return 0;
            }
        }
        return *s1 - *s2;
    }
}

int numcmp (const char *s1, const char *s2, int field_1, int field_2)
{
    char sub_string[MAXLINES];
    double v_1 = 0.0;
    double v_2 = 0.0;
    int len_1 = strlen(s1);
    int len_2 = strlen(s2);

    if (len_1 < field_2 || len_2 < field_2)
    {
        printf ("error: pos_2 exceeds the string\n");
        exit(0);
    }
    
    if ((field_1 && field_2) >= 0)
    {
        substring(sub_string, s1, field_1, field_2);
        
        v_1 = atof(sub_string);

        substring(sub_string, s2, field_1, field_2);

        v_2 = atof(sub_string);
    }
    else
    {
        v_1 = atof(s1);
        v_2 = atof(s2);
    }

        if (v_1 < v_2)
        {
            return -1;
        }
        else if (v_1 > v_2)
        {
            return 1;
        }
        else
        {
            return 0;
        }
}

void substring (char *substring, const char *s, int pos_1, int pos_2)
{
    int i = 0;
    int j = pos_1;

   for (i = 0, j = pos_1; j <= pos_2; i++, j++)
   {
       substring[i] = s[j];
   }
   substring[i] = '\0'; 
}
void swap (void *v[], int i, int j)
{
    void *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
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
