#include <stdio.h>
#include <stdio.h>
#define MAXLINE 1000    /* maximum input line size */
int get_line(char line[], int maxline);
void copy (char to[], char from[]);
int rm_trail_blanks_and_tabs(char buf_from[], char buf_to[]);
/* print longest input line */
main()
{
    int len;            /* current line length */
    int max;            /* maximum length seen so far */
    char line[MAXLINE];     /* current input line */
    char longest[MAXLINE];  /* longest line saved here */
    char line_filtered[MAXLINE];
    int trails;

    max = trails = 0;
    while ((len = get_line(line, MAXLINE)) > 0)
        if  (len > 0) {
            max = len;
            trails = rm_trail_blanks_and_tabs(line, line_filtered);
            copy(longest, line_filtered);
            printf("length: %d, %s", max, line_filtered);
            printf("trails removed: %d\n", trails);
        }
    if (max > 0)    /* there was a line */
        printf("length: %d, %s", max, line_filtered);
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

int rm_trail_blanks_and_tabs(char buf_from[], char buf_to[])
{
    int i, j, removed;

    for (i = 0, j = 0, removed = 0; buf_from[i] != '\0'; ++i) {
        if ((i == 0 && buf_from[0] == ' ') || (i == 0 && buf_from[0] == '\t')) {
            ++i; 
            ++removed;
            while(buf_from[i] == ' ' || buf_from[i] == '\t') {
                ++i;
                ++removed;
            }
        }
        buf_to[j] = buf_from[i];
        ++j;

        if ((buf_from[i] == ' ' && buf_from[i + 1] == ' ') || (buf_from[i] == '\t' && buf_from[i + 1] == '\t')) {
            ++i;
            while(buf_from[i] == ' ' || buf_from[i] == '\t') {
                ++i;
                ++removed;
            }
            --i;
        }
        if ((buf_from[i + 1] == ' ' && buf_from[i + 2] == '\0') || (buf_from[i + 1] == '\t' && buf_from[i + 2] == '\0'))
            i++;
    }
    buf_to[j] = '\0';
    return removed;
}

