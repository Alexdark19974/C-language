
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define  MAXTOKEN 100
#define  BUFSIZE  100

enum  { NAME, PARENS, BRACKETS };

void  dcl(void);
void  dirdcl(void);

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0;
int gettoken(void);
int tokentype;             /* type of last token */
char token[MAXTOKEN];      /* last token string */
char name[MAXTOKEN];       /* identifier name */
char datatype[MAXTOKEN];   /* data type = char, int, etc. */
char out[1000];            /* output string */

int main()  /* convert declaration to words */
{
    while (gettoken() != EOF) { /* 1st token on line */
        strcpy(datatype, token);   /* is the datatype */
        out[0] = '\0';
        dcl();         /* parse rest of line */
        if (tokentype != '\n')
        printf("syntax error\n");
        printf("%s:  %s %s\n", name, out, datatype);
    }
    return 0;
}

int gettoken(void)  /* returns next token */
{
    int c, getch(void); /* getch: get a (possibly pushed back) character */
    void ungetch(int);   /* ungetch:  push character back on input */
    char *p = token;

    while ( (c=getch())==' ' || c=='\t' )   /* skip white space */
        ;
    if ( c=='(' ) {
        if ( (c=getch())==')' ) {
            strcpy(token, "()");
            return tokentype = PARENS;
        }
        else {
            ungetch(c);
            return tokentype = '(';
        }
    }
    else if ( c=='[' ) {
        for(*p++ = c; (*p++ = getch()) != ']'; );
        *p = '\0';
        return tokentype = BRACKETS;
    }
    else if ( isalpha(c) ) {
        for (*p++ = c; isalnum(c=getch()); ) *p++ = c;
        *p = '\0';
        return tokentype = NAME;
    }
    else
        return tokentype = c;
}

int getch(void)     /* get a (possibly pushed back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* pretend to push character back on input */
{
    if (bufp >= BUFSIZE) printf("ungetch:  too many characters\n");
    else buf[bufp++] = c;
}

void dcl(void)      /* parse a declarator */
{
    int ns; /* number of stars */

    for (ns=0; gettoken()=='*'; ) ns++; /* count *'s */
    dirdcl();
    while (ns-- > 0) strcat(out, " pointer to");
}


void dirdcl(void)   /* parse a direct declarator */
{
    int type;

    if ( tokentype=='(' ) {     /* ( dcl ) */
        dcl();
        if ( tokentype != ')' ) printf("error:  missing )\n");
    }
    else if (tokentype == NAME) /* variable name */
        strcpy(name, token);
    else
        printf("error:  expected name or (dcl)\n");

    while( (type=gettoken())==PARENS || type==BRACKETS)
        if (type==PARENS)
            strcat(out, " function returning");
        else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
}
