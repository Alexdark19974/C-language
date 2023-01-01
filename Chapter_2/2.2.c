#include <stdio.h>
#define MAXLINE 1000

int get_line(char line[], int maxline);

main ()
{
    int len;
    int max;
    char line[MAXLINE];
    char longest[MAXLINE];

    max = 0;
    while ((len = get_line(line, MAXLINE)) > 0)
        if (len > 0) {
            max = len;
            printf("line: %s\n", line);
        }

    return 0;
}

int get_line(char line[], int lim)
{
    int c, i;

    for (i=0;(c = getchar())!=EOF; ++i) {
        if (i<lim-1) {
            line[i] = c;
            if (c == '\n') {
                ++i;
                line[i] = '\0';
                return i;
            }
        }
        else {
            line[i] = '\0';
            return i;
        }
    }
    line[i] = '\0';
    return i;
}

