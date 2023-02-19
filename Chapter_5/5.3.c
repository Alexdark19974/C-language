#include <stdio.h>
#define MAXLINE 1000

int get_line(char *, int);
void _strcat(char *, char *);

main()
{
    char str1[MAXLINE] = {0};
    char str2[MAXLINE * 2] = "I am a string";
    int len = 0;
    printf("Enter the string: ");
    while ((len = get_line(str1, MAXLINE) != EOF)) {
        if (len > 0) {
            _strcat(str2, str1);
            printf("The resulting string is %s", str2);
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
