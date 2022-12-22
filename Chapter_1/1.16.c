#include <stdio.h>
#define MAXLINE 1000    /* maximum input line size */

int get_line(char line[], int maxline);
void copy (char to[], char from[]);

/* print longest input line */
main()
{
    int len;            /* current line length */
    int max;            /* maximum length seen so far */
    char line[MAXLINE];     /* current input line */
    char longest[MAXLINE];  /* longest line saved here */

    max = 0;
    while ((len = get_line(line, MAXLINE)) > 0)
        if  (len > max) {
            max = len;
            copy(longest, line);
        }
    if (max > 0)    /* there was a line */
        printf("length: %d, %s", max, longest);
    return 0;
}

/* getline:  read a line into s, return length */
int get_line(char s[], int lim)
{
    int c, i;

    for (i=0; (c=getchar()) != EOF && c != '\n'; ++i)
        if (i<lim-1) // even though the limit is MAXLINE - 1 we keep counting until EOF or newline char is met
            s[i] = c;
        else if (i == lim-1)
            s[i] = '\0';

    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    if (i < lim-1)
        s[i] = '\0';
    return i;
}

/* copy:  copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[])
{
    int i;

    i = 0;
    while ((to[i] = from[i]) != '\0')
        i++;
}
