#include <stdio.h>
#include <limits.h>
#define MAXLINE 1000
#define BIT_MAX 31
#define MASK UINT_MAX
int get_line(char line[], int lim);
unsigned int invert(unsigned int x, unsigned p, unsigned n);
int atoi(char s[]);

main()
{
    int len, num;
    unsigned int x, p, n;
    char line[MAXLINE], ready_to_invert;

    ready_to_invert = x = p = n = 0;

    for (num = 0; num != MAXLINE; ++num)
        line[num] = 0;
    printf("Enter the number: ");
    while ((len = get_line(line, MAXLINE)) > 0) {
        if (len > 0 && !ready_to_invert)
            x = atoi(line);
        else if (len > 0 && ready_to_invert == 1 && p <= BIT_MAX)
            p = atoi(line);
        else if (len > 0 && ready_to_invert == 2 && p >= n) {
            n = atoi(line);
            x = invert(x, p, n);
            printf("Inverted number=%u at the position=%u with bits=%u\n", x, p, n);
            ready_to_invert = -1;
        }
        else {
            printf("error: illegal character or the lack thereof.\n");
            ready_to_invert = -1;
        }
        if (-1 == ready_to_invert)
            printf("Enter the number: ");
        ready_to_invert++;
        if (ready_to_invert == 1)
            printf("Enter the starting position of n-bit range: ");
        if (ready_to_invert == 2)
            printf("Enter the number of bits: ");
    }

    return 0;
}

int get_line(char line[], int lim)
{
    int c, i;

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

unsigned int invert(unsigned int x, unsigned int p, unsigned int n)
{
    return x ^ ((~(MASK << n)) << (p - n));
}
