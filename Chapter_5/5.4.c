#include <stdio.h>
#define MAXLINE 1000

int get_line(char *, int);
void _strcat(char *, char *);
int _strcmp(char *, char *);
int strend(char *, char *);

main()
{
    char str1[MAXLINE] = {0};
    char str2[MAXLINE * 2] = "I am a string";
    int len = 0, is_strcat = 1;
    printf("Enter the string: ");
    while ((len = get_line(str1, MAXLINE) != EOF)) {
        if (len > 0) {
            if (is_strcat) {
                _strcat(str2, str1);
                printf("The resulting string is %s", str2);
            }
            else if (!is_strcat && strend(str2, str1))
                printf("strend() found str1=%s in str2=%s", str1, str2);
            else
                printf("strend() didn't find str1=%s in str2=%s", str1, str2);
            is_strcat == 0 ? is_strcat = 1: is_strcat--;
        }
        printf("Enter the string: ");
    }

    return 0;
}

int get_line(char *s, int lim)
{
    int i, c = 0;

    for (i = 0; (i < lim) && ((c = getchar()) != EOF) && (c != '\n'); ++i)
        s[i] = c;
    if (c =='\n')
        s[i++] = c;

    s[i] = '\0';
    return c == EOF ? EOF : i;
}

void _strcat(char *dest, char *src)
{
    while (*dest++) ;
    dest--;
    while ((*dest++ = *src++)) ;
}

int strend(char *s, char *t) 
{
    int len1 = 0, len2 = 0;
    while(*s++)
        len1++;
    --s;
    while(*t++)
        len2++;
    --t;
    while (*--t == *--s)  {
        if (len2-- == 0 || len1-- == 0) 
            break;
    }
    return len2 == 0 ? 1 : 0;
}

/* strcmp:  return <0 if s < t, 0 if s==t, >0 s>t */
int _strcmp(char *s, char *t)
{
    while (*s++ == *t++) ;
   return  *s == '\0' ? 0 : *s - *t;
}
