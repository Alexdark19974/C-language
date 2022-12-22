
#include <stdio.h>

#define MAXLINE 1000    /* maximum input line size */
#define TABSTOP 8
#define FOLDPOINT 16
int max;            /* maximum length seen so far */
char line[MAXLINE];     /* current input line */
char longest[MAXLINE];  /* longest line saved here */
char folded_line[MAXLINE];
int get_line(void);
void copy(void);
void fold_line(void);
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
            fold_line();
            printf("folded line: %s\n", folded_line);
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

void fold_line(void)
{
    int i, j, counter;

    i = j = counter = 0;

    while (longest[i] != '\0') {
        folded_line[j] = longest[i];
        ++counter;
        if (!(counter % FOLDPOINT)) {
            if (longest[i] != '\t' || longest[i] != ' ') {
                while ((longest[i] != '\0' && longest[i] != '\t') && (longest[i] != '\0' && longest[i] != ' ')) {
                    folded_line[j] = longest[i];
                    ++i; ++j;
                }
            }
            folded_line[j] = '\n'; // FOLDPOINT
            counter = 0;
            ++j;
            folded_line[j] = longest[i];
        }
        if (longest[i] != '\0') {
           ++i; ++j;
       }
    }
    folded_line[j] = '\0';
}
