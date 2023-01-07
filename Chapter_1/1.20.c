#include <stdio.h>
#define MAXLINE 1000    /* maximum input line size */
#define TABSTOP 8
int max;            /* maximum length seen so far */
char line[MAXLINE];     /* current input line */
char longest[MAXLINE];  /* longest line saved here */
char detabed_line[MAXLINE];
int get_line(void);
void copy(void);
void detab(void);
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
            detab();
            printf("detabed line: %s\n", detabed_line);
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

void detab(void)
{
    int i, j, counter;

    i = j = counter = 0;
    while (longest[i] != '\0') {
        detabed_line[j] = longest[i];
        if (longest[i] == '\t') {
            while (counter < TABSTOP) {
                detabed_line[j] = 'b'; // in order to make it easier, ' ' is replaced with 'b'
                ++counter; ++j;
            }
            --j; // to counteract one extra increment from the nested while loop
            counter = -1; // next increment will make it 0
        }
        ++counter; ++i; ++j;
        if (counter == TABSTOP)
            counter = 0;
    }
    detabed_line[j] = '\0';
}

