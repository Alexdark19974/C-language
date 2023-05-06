#include "declaration.h"
#include <ctype.h>
#include <string.h>

int bufp = 0;
char buf[BUFSIZE] = {0};
int gettoken(void)  /* return next token */
{
    extern char parens, token[];
    extern int tokentype;
    int c, getch(void), i = 0;
    void ungetch(int);
    char *p = token;
    char tempbuf[BUFSIZE] = {0};
    static int search_for_qualifier = 0;
    while (((c = getch()) == ' ' || c == '\t'))
        ;
    if (c == '(') {
        if (search_for_qualifier == TRUE) {
            ungetch(c);
            return search_for_qualifier = FALSE;
        }
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
        if (search_for_qualifier == TRUE) {
            ungetch(c);
            return search_for_qualifier = FALSE;
        }
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
        if (search_for_qualifier == TRUE) {
            for (i = 0, tempbuf[i++] = c; isalnum(c = getch()); i++)
                tempbuf[i] = c;
            tempbuf[i] = '\0';
        } else {
            for (*p++ = c; isalnum(c = getch()); )
                *p++ = c;
            *p = '\0';
        }
        ungetch(c);
        if (tokentype ==  BRACKETS) {
            printf("error: name \"%s\" is in the wrong place\n", token);
            return tokentype = ERR;
        }
        if ((tokentype = type_name_check(search_for_qualifier == TRUE ? tempbuf : token)) == TYPE) {
            search_for_qualifier = TRUE;
            if (!*tempbuf)
                gettoken();
            else
                sprintf(&token[strlen(token)], " %s", tempbuf);
        } else if (tokentype == QUALIFIER) {
            if (*tempbuf)
                sprintf(&token[strlen(token)], " %s", tempbuf);
            else {
                search_for_qualifier = TRUE;
                gettoken();
            }
        } else if (search_for_qualifier == TRUE && tokentype == NAME) {
            while(--i >= 0)
                ungetch(tempbuf[i]);
        }
        if (search_for_qualifier == TRUE)
            tokentype = TYPE;
        search_for_qualifier = FALSE;
        return tokentype;
    } else if (c == ']')
        return printf("error: \"[\" is missing\n");
    else if (c == ')')
        tokentype = c , parens++;
    else if (search_for_qualifier == TRUE)
        ungetch(c);
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
        buf[bufp++] = c;
}
