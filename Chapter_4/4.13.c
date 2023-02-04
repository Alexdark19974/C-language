#include <stdio.h>
#include <ctype.h>
#define MAXLINE 1000

int atoi(char[]);
int get_line(char line[], int lim);
int getop(void);

#define swap(t, x, y) if (sizeof(t) == sizeof(x) && sizeof(t) == sizeof(y)) { \
                            t = x, x = y, y = t; \
                            } \
                       else { \
                            printf("Error: swap type is of %lu bytes, but x is of %lu type and y is of %lu type\n", sizeof(t), sizeof(x), sizeof(y)); \
                            return -1; \
                       } \

static char line[MAXLINE] = {0};
static int i = 0;

main() 
{
    int x = 0, y = 0, t = 0, len = 0;
    printf("Enter x and y values: ");
  while ((len = get_line(line, MAXLINE))) {
        if (len > 0) {
            x = getop();
            y = getop();
            printf("Pre-swapped values: x = %d, y = %d\n", x, y);
            swap(t, x, y);
            printf("Post-swapped values: x = %d, y = %d\n", x, y);
            i = 0;
        }
        printf("Enter x and y values: ");
    }
    return 0;
}

int get_line(char line[], int lim)
{
    int j, c;

    c = 0;
    for (j=0;j<lim-1 && (c = getchar())!=EOF && c!='\n'; ++j)
        line[j] = c;

    if (c == '\n')
        line[j++] = c;

    line[j] = '\0';
    return j;
}

int atoi(char s[])
{
    int j, n, sign;

    for (j = 0; isspace(s[j]); j++)  /* skip white space */
        ;
    sign = (s[j] == '-') ? -1 : 1;
    if (s[j] == '+' || s[j] == '-')  /* skip sign */
        j++;
    for (n = 0; isdigit(s[j]); j++)
        n = 10 * n + (s[j] - '0');
    return sign * n;
}

int getop(void)
{
    int bufp = 0;
    char digitBuf[MAXLINE] = {0};

    while (isspace(line[i]))
            i++;
    while (isdigit(line[i]))
        digitBuf[bufp++] = line[i++];
    if (!bufp) {
        i = 0;
        printf("Enter the second digit: \n");
        goto tryagain;
    }
    digitBuf[bufp] = '\0';
    return atoi(digitBuf);

tryagain:
    get_line(line, MAXLINE);
    return getop();
}

