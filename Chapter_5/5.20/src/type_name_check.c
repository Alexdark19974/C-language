#include "declaration.h"

int type_name_check(char *ptr)
{
    int i, j;
    static const char type_qualifier[2][BUFSIZE][MAXTOKEN] = {
        {"char",
        "short",
        "int",
        "long",
        "float",
        "double",
        "void",
        ""},{
        "const",
        "volatile",
        "" }
    };

    for (i = 0; i < 2; i++) {
        for (j = 0; **(*(type_qualifier + i) + j); j++) {
            if (!strcmp(ptr,*(*(type_qualifier + i) + j)))
                return i == 0 ? TYPE : QUALIFIER;
        }
    }
    return NAME;
}

