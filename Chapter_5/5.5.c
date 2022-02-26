#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#define MAX 100

char *strconcat (char *, char *, int);
void strcopy (char *, char *, int);
int strcomp(char *s, char *t, int);


int main(void)
{
    char arr_1[MAX] = "Might and ";
    char arr_2[MAX] = "Magical";
    char arr_3[MAX];

    int number_int = 0;
    scanf ("%d", &number_int );

    char *conc_string_p = strconcat(arr_1, arr_2, number_int);
    printf("%s\n", conc_string_p);

    strcopy(arr_3, arr_2, number_int);
    printf("%s\n", arr_3);

    printf("%d\n", strcomp(arr_1, arr_3, number_int));

    return 0;
}

char *strconcat(char *s, char *t, int n)
{
    char *s_p = s;
    char *t_p = t;
    int counter = 0;

    while (*s_p)
    {
        s_p++;
    }
    
    while ((counter++ != n))
    {
        *s_p++ = *t_p++;
    }
    return s;
}

void strcopy (char *s, char *t, int n)
{
    int counter = 0;
    while ((counter++ != n))
    {
      *s++ = *t++;
    }
    *(s++) = '\0';
}

int strcomp (char *s, char *t, int n)
{
    int counter = 0;

    for (;(counter != n) && (*s == *t); s++, t++)
    {

        if (*s == '\0')
        {
            return (0);
        }

        counter++;
    }
    return *s - *t;
}
