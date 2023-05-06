#include "declaration.h"

/* check if the following characters make a type or name(parameters) or not (in case there's '\n' as the next char), aking to peek_and_gettoken()*/
int check_next_params(int opt)
{
    int i = 0, c = 0;
    char buff[BUFSIZE] = {0};
    extern jmp_buf env;
    extern int square_check, list, asterisk, encapsulate;
    while ((buff[i] = c = getch()) == ' ' || buff[i] == '\t') i++;
    buff[i + 1] = '\0';
    switch (opt) {
        case NAME:
            if ((!isalpha(buff[i]) && buff[i] != '*' && buff[i] != '[' && buff[i] != '(') || square_check == TRUE) {
                if (buff[i] == '\n')
                    ungetch(buff[i]);
                square_check = FALSE;
                print_error("error: name is followed by an illegal symbol (or the position of it is wrong).\n", buff[i]);
            }
            while(i >= 0)
                ungetch(buff[i--]);
            return TRUE;
        case TYPE:
            if (buff[i] == '\n' || encapsulate == TRUE) {
                while(i >= 0)
                    ungetch(buff[i--]);
                return TRUE;
            }
            print_error("error: type must be at the end.\n", NONE);
        default:
            if (opt == ']') {
                if (buff[i] == '(')
                    print_error("error: array cannot be followed by a function.\n", NONE);
                if (!isalpha(buff[i]) && buff[i] != '*' && buff[i] != '['  && buff[i] != ',') {
                    if (buff[i] == '\n')
                        ungetch(buff[i]);
                    print_error("error: array must be followed by a type or a pointer or another array\n", buff[i]);
                } else if (isalpha(buff[i])) {
                    square_check = TRUE;
                    if (check_name_or_type(buff[i]) != ERR) {
                        return square_check = FALSE;
                    }
                } else if (buff[i] == ',') {
                    if (asterisk > 0)
                        ungetch(buff[i]);
                    return COMMA;
                } else if (buff[i] == '[' && list) {
                    ungetch('[');
                    return '[';
                }
                while(i >= 0)
                    ungetch(buff[i--]);
                return TRUE;
            }
            if (buff[i] == '\n')
                ungetch(buff[i]);
    }
    return print_error("error: unknown error.\n", NONE);
}

int check_brackets(int c)
{
    int i = 0;
    static int ret = 0;
    char buff[BUFSIZE] = {0};
    extern int tokentype, asterisk, recursive, list;
    extern char token[], out[];

    for (buff[i++] = c; (c = buff[i++] = getch()) != ']' && c != '[' && c != '\n' && (isdigit(c) || c == ' ' || c == '\t');) ; 
    buff[i] = '\0';
    if (c == '\n')
        ungetch(c);
    /* inspect in case there are syntax-related errors */
    if (*token != '[')
        print_error("error: \"[\" is missing\n", NONE);
    else if (buff[i - 1] != ']' && c == '\n')
        print_error("error: \"]\" is missing\n", NONE);
    else if  (buff[i - 1] != ']' && c != '\n')
        print_error("error: illegal value.\n", buff[i - 1]);
    else if ((ret = check_next_params(']')) == ERR)
        return ERR;
    /* if asterisk, put all the characters back onto input, deal with them later */
    if (asterisk > 0)
        while(--i >= 0)
            ungetch(buff[i]);
    else
        strcat(token, buff);
    /* encapsulate name if asterisk met, then deal with the characters */
    return asterisk > 0 ? tokentype = ENCAP_TOKEN | ASTERISK : ret == COMMA ? tokentype = BRACKETS | COMMA : (tokentype = BRACKETS);

}

int check_function_params(int c)
{
    extern char token[], out[];
    extern int tokentype, asterisk, list, encapsulate;
    int i = 0;
    char buff[BUFSIZE] = {0};
    for (buff[i++] = c; (c = buff[i++] = getch()) != ')' && c != '(' && c != '\n' &&  !isalnum(c) && ( c == ' ' || c == '\t');) ;
    buff[i] = '\0';
    /* if asterisk, put characters back onto the input, and deal with them later */
    if (asterisk > 0)
        while (--i >= 0)
            ungetch(buff[i]);
    else {
        if (*token == '(' && *buff == ')') {
            *(token + 1) = ')';
            while (--i > 0)
                ungetch(buff[i]);
            return tokentype = PARENS;
        } else if (*token == '(' && isalpha(*buff)) {
            strcat(out, token);
            while (--i >= 0)
                ungetch(buff[i]);
            encapsulate = TRUE;
            return '(';
        }
        else if (*token == '(' && !isalpha(*(buff + 1))) {
            if (*(buff + 1) == '*')
                print_error("error: \"*\" cannot be right after the opening parenthesis\n", NONE);
            print_error("error: illegal value.\n", *(buff + 1));
        }
        else {
            strcat(token, buff);
            return tokentype = PARENS;
        }
    }
    /* encapsulate the name if asterisk met before parsing function parameters */
    return asterisk > 0 ? tokentype = ENCAP_TOKEN | ASTERISK : (tokentype = PARENS);
}

/* check if anything non-'[' or non-'C' */
int check_name_or_type(int c)
{
    int i = 0, ret = 0;
    extern jmp_buf env;
    char buff[BUFSIZE] = {0};
    extern int tokentype, asterisk, square_check, list, encapsulate;
    extern char token[], out[];

    /* iterate until a non-space character is found */
    for (buff[i++] = c; isalnum(c = getch()); i++)
        buff[i] = c;
    buff[i] = '\0';
    ungetch(c);

    /* establish if a name or type and inspect accordingly */
    switch ((ret = type_name_check(buff))) {
        case TYPE:
            if ((c == '\n' && !out[0]) || check_next_params(TYPE) == ERR)
                print_error("error: name is missing or int must be at the end\n", NONE);
            break;
        case NAME:
            if ( c == '\n' || check_next_params(NAME) == ERR)
                print_error("error: name must be followed by type or brackets or function.\n", NONE);
            break;
        default:
            print_error("error: unknown error.\n", NONE);
    }
    /*if asterisk, put all the characters back onto input and deal with them later */
    if (asterisk > 0 || square_check == TRUE)
        while (--i >= 0)
            ungetch(buff[i]);
    else if (list == FALSE)
        strcpy(token, buff);
    else 
        strcat(token, buff);
    return asterisk > 0 ? ASTERISK : (tokentype = (tokentype ^ tokentype) | NAME);
}

