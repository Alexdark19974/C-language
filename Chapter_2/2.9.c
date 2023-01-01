#include <stdio.h>
#include <limits.h>
#define MAXLINE 1000
#define BIT_MAX 32
#define MASK UINT_MAX
int get_line(char line[], int lim);
int bitcount(unsigned int x);
int atoi(char s[]);

main()
{
    int len;
    unsigned int x, n;
    char line[MAXLINE];

    x = n = 0;

    for (n = 0; n != MAXLINE; ++n)
        line[n] = 0;

    printf("Enter the number: ");
    while ((len = get_line(line, MAXLINE)) > 0) {
        if (len > 0) {
            x = atoi(line);
            x = bitcount(x);
            printf("the number of 1 bits: %u\n", x);
        }
    }

    return 0;
}

int get_line(char line[], int lim)
{
    int i, c;

    c = 0;
    for (i=0;i<lim-1 && (c = getchar())!=EOF && c!='\n'; ++i)
        line[i] = c;

    if (c == '\n')
        line[i++] = c;

    line[i] = '\0';
    return i;
}

int atoi(char s[])
{
    int i, n;

    n = 0;
    for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i)
        n = 10 * n + (s[i] - '0');
    return n;
}

/* bitcount: count 1 bits in x */
int bitcount(unsigned int x)
{
    int b;

    for (b = 0; x != 0; x &= (x - 1))
            b++;
    return b;
}

