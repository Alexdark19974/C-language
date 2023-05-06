#include "declaration.h"

int tokentype;              /* type of last token */
char token[MAXTOKEN];       /*last token string */
char name[MAXTOKEN];        /*identifier name */
char datatype[MAXTOKEN];    /* data type = char, int, etc. */
char out[1000];             /* output string */
char parens = 0; /* find an opening bracket (TRUE), make FALSE if closing bracket met*/
main()  /* convert declaration to words */
{
    while (gettoken() != EOF) {    /* 1st token on line */
        if (tokentype == TYPE)
            strcpy(datatype, token);   /* is the datatype */
        else if (tokentype == NAME) {
            printf("syntax error: name cannot be type or type is not correct\n");
            continue;
        }
        else
            continue;
        out[0] = '\0';
        dcl();       /* parse rest of line */
        if (tokentype != '\n' || parens % 2) {
            printf("syntax error");
            if (parens % 2)
                printf(": \"(\" or \")\" is missing");
            putchar('\n');
        }
        else
            printf("%s: %s %s\n", !name[0] ? "generic" : name , out, datatype);
        memset(name, 0, sizeof(name));
        memset(out, 0, sizeof(out));
        memset(datatype, 0, sizeof(datatype));
        parens = tokentype = FALSE;
    }
    return 0;
}
