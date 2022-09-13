#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
#define MAXNAME 25
#define DATASIZE 25
#define OUTSIZE 100
#define BUFSIZE 100
#define TEMPSIZE 100

enum { NAME, PARENS, BRACKETS, TYPE };

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next available position in buf */

int gettoken(void);

int tokentype = 0;          /* type of last token */
char token[MAXTOKEN];       /* last token - лексема string */
char name[MAXNAME];         /* the name of the (identifier) */
char data_type[DATASIZE];   /* type of data : char, int, etc. */
char out[OUTSIZE];          /* resulting string */

int main(void) /* convert declarations to words */
{
    int type = 0;
    char temp[TEMPSIZE];

    while (gettoken() != EOF) { /* 1st token from string */
        strncpy(out, token, sizeof(out));
        temp[sizeof(out) - 1] = '\0';
        while ((type = gettoken()) != '\n')
            if (type == PARENS || type == BRACKETS)
                strcat(out, token); 
            else if (type == '*') {
                sprintf(temp, "(*%s)", out);
                strcpy(out, temp);
            } else if (type == NAME) {
                sprintf(temp, "%s %s", token, out);
                strcpy(out, temp);
            } else
                printf("invalid input at %s\n", token);
        printf("%s\n", out);
    }
    return 0;
}

int gettoken(void)
{
    int c = 0;
    int getch(void);
    void ungetch(int);
    char *ptr = token;
    static int first_round_bracket = 0;

    while ((c = getch()) == ' ' || c == '\t')
        ;

    if (c == '(') {
        first_round_bracket = 1;
        if ((c = getch()) == ')') {
            first_round_bracket = 0;
            return tokentype = PARENS;
        } else
            if (!isalnum(c) && c != '*')
                printf("error: missing ')'\n");
                exit(0);
            ungetch(c);
            return tokentype = '(';
    } else if (c == '[') {
        *ptr = c;
         ptr++;

        for (*ptr = c; (*ptr = getch()) != ']' && *ptr != '\n';)
            ptr++;

        if (*ptr != ']')
          printf ("error: missing ']'\n");
          exit(0);

        ++ptr;
        *ptr = '\0';

        return tokentype = BRACKETS;
     } else if (isalpha(c)) {
        *ptr = c;
        ptr++;

        for (*ptr = c; (*ptr = getch()) != ' ' && *ptr != ')' && *ptr != ']' && *ptr != '\n'; ptr++) {
            switch (*ptr) {
                case '(':
                    first_round_bracket = 1;
                    ungetch(*ptr);
                    *ptr = '\0';
                    return tokentype = NAME;
                case '[':
                    ungetch(*ptr);
                    *ptr = '\0';
                    return tokentype = NAME;
            }
        }

        if (*ptr == ']')
            return tokentype = *ptr;
        else if (*ptr == ')') {
            if (!first_round_bracket)
                return tokentype = *ptr;
            else
                ungetch(*ptr);
                *ptr = '\0';
                first_round_bracket = 0;
                return tokentype = NAME;
        }

        if (*ptr == '\n')
            ungetch(*ptr);
        *ptr = '\0';
        ptr = token;

        if (strcmp("char", ptr) == 0|| strcmp("int", ptr) == 0 || strcmp("double", ptr) == 0 || strcmp("long", ptr) == 0 || strcmp("float", ptr) == 0 || strcmp("void", ptr) == 0)
            return tokentype = TYPE;
        return tokentype = NAME;
    }
    return tokentype = c;
}

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
       buf[bufp] = c;
       bufp++;
}
