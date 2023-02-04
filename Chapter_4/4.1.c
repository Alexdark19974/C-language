#include <stdio.h>
#include <string.h>
#define MAXLINE 1000    /* maximum input line length */

int get_line(char line[], int max);
int strindex(char source[], char searchfor[]);

char pattern[] = "ould";    /* pattern to search for */

/* find all lines matching pattern */
main()
{
    char line[MAXLINE];
    int found = 0, idx = 0;

    while (get_line(line, MAXLINE) > 0)
        if ((idx = strindex(line, pattern)) >= 0) {
            printf("the rightmost occurence=%d, line: %s", idx, line);
            found++;
        }
    return found;
}

/* getline: get line into s, return length */
int get_line(char s[], int lim)
{
    int c, i;

    i = c = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c!= '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

/* strindex: return index of t in s, -1 if none */
int strindex(char s[], char t[])
{
    int i, j, k;

    for (i = strlen(s) - 1; i >= 0; i--) {
        for (j=i, k = strlen(t) - 1; k >= 0 && s[j]==t[k]; j--, k--)
            ;
        if (k <= 0)
            return j;
    }
    return -1;
}

