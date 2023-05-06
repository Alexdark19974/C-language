#include "declaration.h"
#include <ctype.h>

int bufp = 0;
char buf[BUFSIZE] = {0};
int gettoken(void)  /* return next token */
{
    extern char parens, token[];
    extern int tokentype;
    int c, getch(void);
    void ungetch(int);
    char *p = token;

    while (((c = getch()) == ' ' || c == '\t'))
        ;
    if (c == '(') {
        parens++;
        if ((c = getch()) == ')') {
            strcpy(token, "()");
            parens++;
            return tokentype = PARENS;
        } else {
            ungetch(c);
            if (c == '\n' || c == EOF)
                return ERR;
            return tokentype = '(';
        }
    }
    else if (c == '[') {
        for (*p++ = c; ((*p++ = getch()) != ']' && *(p - 1) != '[') && (*(p - 1) != '\n' && *(p - 1) != '\0'); )
            ;
        *p = '\0';
        if (*(p - 1) != ']') {
          /*  if (*(p - 1) == '\n') */
                ungetch((*(p - 1)));
            return printf("error: \"]\" is missing\n");
        }
        return tokentype = BRACKETS;
    }
    else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getch()); )
            *p++ = c;
        *p = '\0';
        ungetch(c);
        if (tokentype ==  BRACKETS) {
            printf("error: name \"%s\" is in the wrong place\n", token);
            return tokentype = ERR;
        }
        return tokentype = type_name_check(token);
    } else if (c == ']')
        return printf("error: \"[\" is missing\n");
    else if (c == ')')
        tokentype = c , parens++;
    else
        return tokentype = c;
    return 0;
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
        buf[bufp++] = c;
}
