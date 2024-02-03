#include <stdio.h>
#include <stdio.h>
#define MAXLINE 1000    /* maximum input line size */
int get_line(char line[], int maxline);
void copy (char to[], char from[]);
void reverse(char buf[]);
/* print longest input line */
main()
{
    int len;            /* current line length */
    int max;            /* maximum length seen so far */
    char line[MAXLINE];     /* current input line */
    char longest[MAXLINE];  /* longest line saved here */

    max = 0;
    while ((len = get_line(line, MAXLINE)) > 0)
        if  (len > 0) {
            max = len;
            printf("origin line: %s", line);
            reverse(line);
            printf("reversed line %s", line);
        }

    return 0;
}

/* getline:  read a line into s, return length */
int get_line(char s[], int lim)
{
    int c, i;

    for (i=0; i<lim-1 && (c=getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;

    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

void reverse(char buf[])
{
    int i, j, len, tmp;

    for (i = 0, len = 0; buf[i] != '\0'; ++i)
        ++len;
    if (buf[len - 1] == '\n')
        --len;
    for (i = 0, j = len - 1; i < (len / 2); ++i, --j) {
        tmp = buf[i];
        buf[i] = buf[j];
        buf[j] = tmp;
    }
}

