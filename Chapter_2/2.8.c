#include <stdio.h>
#include <limits.h>
#define MAXLINE 1000
#define BIT_MAX 32
#define MASK UINT_MAX
int get_line(char line[], int lim);
unsigned int rightrot(unsigned int x, unsigned int n);
int atoi(char s[]);

main()
{
    int len;
    unsigned int x, n;
    char line[MAXLINE], ready_to_rotate;

    ready_to_rotate = x = n = 0;

    for (n = 0; n != MAXLINE; ++n)
        line[n] = 0;

    printf("Enter the number: ");
    while ((len = get_line(line, MAXLINE)) > 0) {
        if (len > 0 && !ready_to_rotate)
            x = atoi(line);
        else if (len > 0 && ready_to_rotate) {
            n = atoi(line);
            x = rightrot(x, n);
            printf("number=%u rotate by n bit positions=%u\n", x, n);
            ready_to_rotate = -1;
        }
        else {
            printf("error: illegal character or the lack thereof.\n");
            ready_to_rotate = -1;
        }
        if (-1 == ready_to_rotate)
            printf("Enter the number: ");
        ready_to_rotate++;
        if (ready_to_rotate == 1)
            printf("Enter the number of bits to rotate: ");
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

unsigned int rightrot(unsigned int x, unsigned int n)
{
    return ((x << (BIT_MAX - n)) | ((x & (MASK << n)) >> n)); 
}

