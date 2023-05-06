#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAXLINE 1000    /* maximum input line size */
#define TABSTOP 8

int get_line(char *, int);
void copy(void);
void entab(char *, char *, int);
void detab(char *, char *, int);

/* print longest input line */
main(int argc, char **argv)
{
    enum { DETAB = 0, ENTAB = 1 };
    int tabstop, len, is_entab;
    char line[MAXLINE], deentabbed_line[MAXLINE];

    if (argc > 1) {
        if (**(++argv) == '-')
            ++(*argv) != NULL && **argv == 'e' ? is_entab = ENTAB : (is_entab = DETAB);
        ++(*argv) != NULL &&(isdigit(**(++argv))) ? tabstop = atoi(*argv) : (tabstop = TABSTOP);
    }
    printf("\"-e\" - entab mode, \"-d\" - detab mode, \"t\" - tab, \"b\" - blank, tabstop = %d\n", tabstop);
    while ((len = get_line(line, MAXLINE)) > 0) {
        if (*line == '\n')
            continue;
        printf("%s", is_entab == ENTAB ? "entab mode\n" : "detab mode\n");
        switch (is_entab) {
            case ENTAB:
                entab(deentabbed_line, line, tabstop);
                break;
            case DETAB:
                detab(deentabbed_line, line, tabstop);
                break;
            default:
                goto error;
        }
        printf("%s %s\n", is_entab == ENTAB ? "entabbed line: " : "detabbed line: ", deentabbed_line);
    }
    return printf("Succesfully finished.\n");
error:
    printf("Finished with an error: such a mode doesn't exist.\n");
}

/* getline: read a line into s, return length */
int get_line(char *line, int max)
{
    int c, i;

    for (i=0; i<max-1 && (c = getchar()) != EOF && c!='\n'; i++)
        line[i] = c;
    if (c == '\n') {
        line[i] = c;
        ++i;
    }
    line[i] = '\0';
    return i;
}

void entab(char *entabbed_line, char *line, int tabstop)
{
    int counter = 0, temp;

    while (*line) {
        if (!counter && *line == ' ' && *(line + 1) == ' ') {
            while (*line == ' ') {
                line++, ++counter;
                if ((counter % tabstop) == 0) {
                    *entabbed_line = 't'; entabbed_line++; counter = 0;
                }
            }
            temp = counter % tabstop;
            while (temp > 0) {
                *entabbed_line = 'b'; entabbed_line++; --temp;
            }
        }
        *entabbed_line = *line;
        if (*line == ' ' && *(line + 1) == ' ') {
            while (*line == ' ') {
                line++; ++counter;
                if ((counter % tabstop) == 0) {
                   *entabbed_line = 't'; entabbed_line++; counter = 0;
                }
            }
            if (counter > 0 && (counter % tabstop) == 0)
                --counter;
            temp = counter % tabstop;
            while (temp > 0) {
               *entabbed_line = 'b';
                entabbed_line++; --temp;
            }
            line--; entabbed_line--;
        }
        line++; entabbed_line++; ++counter;
    }
    *entabbed_line = '\0';
}

void detab(char *detabbed_line, char *line, int tabstop)
{
    int counter = 0;

    while (*line != '\0') {
        *detabbed_line = *line;
        if (*line == '\t') {
            while (counter < TABSTOP) {
                *detabbed_line++ = 'b'; // in order to make it easier, ' ' is replaced with 'b'
                ++counter;
            }
            detabbed_line--; // to counteract one extra increment from the nested while loop
            counter = -1; // next increment will make it 0
        }
        ++counter; line++; detabbed_line++;
        if (counter == TABSTOP)
            counter = 0;
    }
    *detabbed_line = '\0';
}
