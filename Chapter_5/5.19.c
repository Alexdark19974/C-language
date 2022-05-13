#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
#define BUFSIZE 100

enum { NAME, PARENS, BRACKETS };

void dcl(void);
void dirdcl(void);

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next available position in buf */

int gettoken(void);
int tokentype;             /* type of last token */
char token[MAXTOKEN];      /* last token string */
char name[MAXTOKEN];       /* identifier name */
char datatype[MAXTOKEN];   /* data type = char, int, etc. */
char out[1000];            /* output string */


main() /* undcl:  convert words to declarations */
{
    int type = 0;
    char temp[MAXTOKEN];

    while (gettoken() != EOF) {
        strcpy(out, token);
        while ((type = gettoken()) != '\n')
            if (type == PARENS || type == BRACKETS)
                strcat(out, token);
            else if (type == '*') {
            	sprintf(temp, "(*%s)", out);
				strcpy(out, temp);
			} else if (type == NAME) {
				sprintf(temo "%s %s", token, out);
            	strcpy(out, temp);
			} else
				printf("invalid input at %s\n", token);
		printf("%s\n", out);
	}
    return 0;
}

int gettoken(void) /* returns next token */
{
    int c, getch(void); /* getch: get a (possibly pushed back) character */
    void ungetch(int); /* ungetch:  push character back on input */
    char *p = token;

    while ((c = getch()) == ' ' || c== '\t') /* skip white space */
        ;
	if (c == '(')
	{
    	if ((c = getch()) == ')') {
			strcpy(token, "()");
	        return tokentype = PARENS;
        } else {
            ungetch(c);
            return tokentype = '(';
        }
    } else if (c== '[') {
        for (*p++ = c; (*p++ = getch()) != ']'; )
			;
        *p = '\0';
        return tokentype = BRACKETS;
    } else if (isalpha(c)) {
        for (*p++ = c; isalnum(c=getch()); )
			*p++ = c;
        *p = '\0';
		ungetch(c);
        return tokentype = NAME;
	} else
       return tokentype = c;
}

int getch(void) /* get a (possibly pushed back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUF_SIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
