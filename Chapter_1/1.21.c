#include <stdio.h>

#define MAXLINE 1000    /* maximum input line size */
#define TABSTOP 8
int max;            /* maximum length seen so far */
char line[MAXLINE];     /* current input line */
char longest[MAXLINE];  /* longest line saved here */
char entabbed_line[MAXLINE];
int get_line(void);
void copy(void);
void entab(void);
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
            entab();
            printf("entabbed line: %s\n", entabbed_line);
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

void entab(void)
{
    int i, j, counter, temp;
    /* alexander  petrov > alexander\t petrov
     *' '' '' ' - \t\t' '*/
    i = j = counter = 0;
    while (longest[i] != '\0') {
        if (i == 0 && longest[i] == ' ' && longest[i + 1] == ' ') {
            while (longest[i] == ' ') {
                ++i; ++counter;
                if ((counter % TABSTOP) == 0) {
                    entabbed_line[j] = 't'; counter = 0; ++j;
                }
            }
            temp = counter % TABSTOP;
            while (temp > 0) {
                entabbed_line[j] = 'b'; j++; --temp;
            }
        }
        entabbed_line[j] = longest[i];
        if (longest[i] == ' ' && longest[i + 1] == ' ') {
            while (longest[i] == ' ') {
                ++i; ++counter;
                if ((counter % TABSTOP) == 0) {
                    entabbed_line[j] = 't'; counter = 0; ++j;
                }
            }
            if (counter > 0 && (counter % TABSTOP) == 0)
                --counter;
            temp = counter % TABSTOP;
            while (temp > 0) {
                entabbed_line[j] = 'b';
                j++; --temp;
            }
            --j; --i;
        }
        ++i; ++j; ++counter;
    }
    entabbed_line[j] = '\0';
}
