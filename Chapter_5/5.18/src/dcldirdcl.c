#include "declaration.h"

/* dcl: parse a declarator */
void dcl(void)
{
    extern char out[];
    extern int tokentype;
    int ns;

    for (ns = 0; gettoken() == '*'; )   /* count *'s */
        ns++;
    if (tokentype == ERR)
        return;
    dirdcl();
    while (ns--> 0)
        strcat(out, " pointer to ");
}

/* dirdcl:  parse a direct declarator */
void dirdcl(void)
{
    int type;
    extern int tokentype;
    extern char parens, name[], token[], out[], datatype[];
    if (tokentype == '(') {             /* ( dcl ) */
        dcl();
        if (tokentype != ')')
            return;
    } else if (tokentype == NAME)     /* variable name */
        strcpy(name, token);
    else if (tokentype == TYPE) {    /* if type later in the code, proceed as if start */
        strcpy(datatype, token);
        dcl();
    }
    else {
        printf("error: expected name or (dcl)\n");
        return;
    }
    while (tokentype != '\n' && ((type = gettoken()) == PARENS || type == BRACKETS))
        if (type == PARENS)
            strcat(out, "function returning");
        else {
            strcat(out, "array");
            strcat(out, token);
            strcat(out, " of");
        }
}
