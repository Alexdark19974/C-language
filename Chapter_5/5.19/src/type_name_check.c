#include "declaration.h"

int type_name_check(char *ptr)
{
    int i;
    static char typeArr[BUFSIZE][MAXTOKEN] = {
        "char",
        "short",
        "int",
        "long",
        "float",
        "double",
        "void",
        ""
    };

    for (i = 0; *typeArr[i]; i++)
        if (!strcmp(ptr, typeArr[i]))
            return TYPE;
    for (i = 0; ptr[i] && isalnum(ptr[i]); i++) ;
    return ptr[i] ? ERR : NAME;
}
