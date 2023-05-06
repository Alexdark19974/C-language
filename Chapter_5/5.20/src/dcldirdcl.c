#include "declaration.h"

/* dcl: parse a declarator */
void dcl(void)
{
    extern char out[], parens;
    extern int tokentype;
    int ns;

    for (ns = 0; gettoken() == '*'; )   /* count *'s */
        ns++;
    if (tokentype == ERR)
        return;
    if (ns && parens && !(parens % 2))
        tokentype = '*';
    dirdcl();
    while (ns--> 0) {
        strcat(out, "pointer to ");
    }
}

/* dirdcl:  parse a direct declarator */
void dirdcl(void)
{
    int type;
    extern int tokentype;
    extern char name[], token[], out[], datatype[];
    if (tokentype == '(') {             /* ( dcl ) */
        dcl();
        if (tokentype != ')')
            return;
    } else if (tokentype == NAME)     /* variable name */
        strcpy(name, token);
    else if (tokentype == TYPE) {    /* if type later in the code, proceed as if start */
        strcpy(datatype, token);
        dcl();
    } else if (tokentype == '*') {
        printf("warning: casting to a function or type does not equal to declaration. Casting is not supported.\n");
        tokentype = ')';
        return;
    } else {
        printf("error: expected name or (dcl)\n");
        return;
    }
    while (tokentype != '\n' && ((type = gettoken()) == PARENS || type == BRACKETS))
        if (type == PARENS)
            strcat(out, "function returning");
        else {
            if (*out && !strstr(out, "of ") && out[strlen(out) - 1] != ' ')
                strcat(out, " ");
            strcat(out, "array");
            strcat(out, token);
            strcat(out, " of");
        }
    if (*out && out[strlen(out) - 1] != ' ')
        strcat(out, " ");
}
