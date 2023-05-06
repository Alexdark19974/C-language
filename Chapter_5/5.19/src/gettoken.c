#include "declaration.h"
int bufp = 0;
char buf[BUFSIZE] = {0};
int gettoken(int prev_token)  /* return next token */
{
    extern char parens, token[], out[];
    extern int tokentype, asterisk, recursive, encapsulate, list;
    int c;
    if (bufp && prev_token == SKIP_TOKEN) {
        while ((c = getch()) != '\n') ;
        return tokentype = c;
    } else if (!bufp && prev_token == SKIP_TOKEN)
        return TRUE;
    while ((prev_token == NONE || prev_token == ASTERISK) && ((c = getch()) == ' ' || c == '\t')) ;
    if (c == ')' && encapsulate == TRUE) {
        strcat(out, ") ");
        list = FALSE;
        return ')';
    }
    if (c == ',' && encapsulate == TRUE) {
        list = TRUE;
        strcat(out, ", ");
        return ',';
    }
    if (c == '[') {
        *token = c;
        return gettoken(NONE);
    }
    else if (c == '(') {
        *token = c;
        return gettoken(NONE);
    }
    if (isalnum(c) || c == ')')
        /* keep retrieving chars and inspecting them down the line, akin to nested gettoken()*/
        return tokentype = iterate_through(c);
    else if (c == ']')
        print_error("error: \"[\" is missing.\n", NONE);
    else if (*token != '(' && c == ')')
        print_error("error: \"(\" is missing.\n", NONE);
    else if (c == '*') {
        if (asterisk < 0)
            asterisk = 0;
        asterisk++;
        /* if asterisk, accumulate */
        return gettoken(ASTERISK);
    }
    else if (c == '\n')
        return tokentype = c;
    return tokentype = gettoken(SKIP_TOKEN);
}

int getch(void)
{
    int c = 0;
    return (bufp > 0) ? buf[--bufp] : (c = getchar());
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

/* inspect chars further from the input, put them back onto input if necessary */
int iterate_through(int c)
{
    extern int asterisk, tokentype;
    extern char token[], out[];
    if (*token == '[')
        return check_brackets(c);
    else if (*token == '(' || (*token == '(' && c == ')'))
        return check_function_params(c);
    return check_name_or_type(c);
}

