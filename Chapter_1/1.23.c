#include <stdio.h>

#define MAXLINE 1000    /* maximum input line size */
#define TABSTOP 8
#define FOLDPOINT 16
int max;            /* maximum length seen so far */
char line[MAXLINE];     /* current input line */
char longest[MAXLINE];  /* longest line saved here */
char no_comment_line[MAXLINE];
int get_line(void);
void copy(void);
void rm_comment(void);
/* print longest input line */
main()
{
    int len;
    extern int max;
    extern char longest[];

    max = 0;
    while ((len = get_line()) > 0)
        if (len > 0) {
            max = len;
            copy();
            rm_comment();
            printf("line w/o comments: %s", no_comment_line);
        }
    return 0;
}

/* getline: read a line into s, return length */
int get_line(void)
{
    int c, i;
    extern char line[];

    for (i=0; i<MAXLINE-1 && (c = getchar()) != EOF && c!='\n'; i++)
        line[i] = c;
    if (c == '\n') {
        line[i] = c;
        ++i;
    }
    line[i] = '\0';
    return i;
}

/* copy: sepcialized version */
void copy(void)
{
    int i;
    extern char line[], longest[];

    i = 0;
    while ((longest[i] = line[i]) != '\0')
        ++i;
}

void rm_comment(void)
{
    int i, j, len, isComment = 0;

    i = j = len = 0;
    while (longest[i] != '\0') {

        if (longest[i] == '/' && longest[i + 1] == '/') {
            while (longest[i] != '\n' && longest[i] != '\0') {
                ++i;
            }
        }
        else if (longest[i] == '/' && longest[i + 1] == '*') {
            for (len = i; !isComment  &&  longest[len] != '\0'; ++len) {
                if (((i + 1) != len && i != (len + 1)) && longest[len + 1] != '\0' && longest[len] == '*' && longest[len + 1] == '/')
                    isComment = len + 2;
            }
            if (isComment)
                i = isComment;
        }
        no_comment_line[j] = longest[i];
        if (longest[i] != '\0') {
            ++i; ++j; isComment = 0;
        }
    }
    no_comment_line[j] = '\0';
}
