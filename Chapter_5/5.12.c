#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAXLINE 1000    /* maximum input line size */
#define TABSTOP 8

int get_line(char *, int);
void copy(void);
void entab(char *, char *, int, int);
void detab(char *, char *, int, int);

/* print longest input line */
main(int argc, char **argv)
{
    enum { DETAB = 0, ENTAB = 1 };
    int tabstop =-1, m = -1, n = -1, len, is_entab = ENTAB;
    char line[MAXLINE], deentabbed_line[MAXLINE];

    if (argc <= 1)
        goto arg_error;
    while(*++argv != NULL) {
        if (**argv == '-' || **argv == '+' || isdigit(**argv)) {
            switch(*(++*argv)) {
                case 'e':
                    printf("entab ");
                    break;
                case 'd':
                    is_entab = DETAB;
                    printf("detab ");
                    break;
                case 'm':
                    if (isdigit(**(++argv)))
                        printf("-m %d ", m = atoi(*argv));
                    else goto error;
                    break;
                case 'n':
                    if (isdigit(**(++argv)))
                        printf("+n %d ", n = atoi(*argv));
                    else goto error;
                    break;
                default:
                    goto error;
                    break;
            };
        }
    }
    putchar('\n');
    if (n <= 0)
        n = TABSTOP;
    printf("Enter the line: ");
    while ((len = get_line(line, MAXLINE)) > 0) {
        if (*line == '\n')
            continue;
        switch (is_entab) {
            case ENTAB:
                entab(deentabbed_line, line, m, n);
                break;
            case DETAB:
                detab(deentabbed_line, line, m, n);
                break;
            default:
                goto error;
        }
        printf("%s %s\n", is_entab == ENTAB ? "entabbed line: " : "detabbed line: ", deentabbed_line);
        printf("Enter the line: ");
    }
    return printf("Succesfully finished.\n");
error:
    return printf("Finished with an error: such a mode doesn't exist.\n");
arg_error:
    return printf("error: not enough arguments.\n");
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

void entab(char *entabbed_line, char *line, int m, int n)
{
    int counter = 0, temp;

    while (*line) {
        if (!counter && counter >= m && *line == ' ' && *(line + 1) == ' ') {
            while (*line == ' ') {
                line++, ++counter;
                if ((counter % n) == 0) {
                    *entabbed_line = 't'; entabbed_line++; counter = 0;
                }
            }
            temp = counter % n;
            while (temp > 0) {
                *entabbed_line = 'b'; entabbed_line++; --temp;
            }
        }
        *entabbed_line = *line;
        if (counter >= m && *line == ' ' && *(line + 1) == ' ') {
            while (*line == ' ') {
                line++; ++counter;
                if ((counter % n) == 0) {
                   *entabbed_line = 't'; entabbed_line++; counter = 0;
                }
            }
            if (counter > 0 && (counter % n) == 0)
                --counter;
            temp = counter % n;
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

void detab(char *detabbed_line, char *line, int m, int n)
{
    int counter = 0;

    while (*line != '\0') {
        *detabbed_line = *line;
        if (counter >= m && *line == '\t') {
            int i = counter % n;
            while (i < n) {
                *detabbed_line++ = 'b'; // in order to make it easier, ' ' is replaced with 'b'
                ++counter; i++;
            }
            detabbed_line--; // to counteract one extra increment from the nested while loop
        }
        ++counter; line++; detabbed_line++;
    }
    *detabbed_line = '\0';
}
