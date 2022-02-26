#include <stdio.h>
#define MAX 100

char *strconcat (char *, char *);

int main(void)
{
    char arr_1[MAX] = "Might and ";
    char arr_2[MAX] = "Magic";

    char *conc_string_p = strconcat(arr_1, arr_2);
    printf("%s\n", conc_string_p);

    return 0;
}

char *strconcat(char *s, char *t)
{
    char *s_p = s;
    char *t_p = t;

    while (*s_p)
    {
        s_p++;
    }
    
    while ((*s_p++ = *t_p++))
    {
        ;
    }
    return s;
}