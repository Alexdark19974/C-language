#include <stdio.h>
#include <limits.h>
#define MAXLINE 1000
#define BIT_MAX 32
#define MASK UINT_MAX
int get_line(char line[], int lim);
int lower(int c);

main()
{
    int len;
    unsigned n;
    char line[MAXLINE];

    for (n = 0; n != MAXLINE; ++n)
        line[n] = 0;

    while ((len = get_line(line, MAXLINE)) > 0) {
        if (len > 0) {
            for (n = 0; line[n] != '\0' && (line[n] = lower(line[n])) != '\n'; ++n)
                ;
            printf("lowered line: %s", line);
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

/* lower: convert c to lower case; ASCII only */
int lower(int c)
{
    return (c >= 'A' && c <= 'Z') ? (c + 'a' - 'A') : c;
}

