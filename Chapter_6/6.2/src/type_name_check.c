#include "bintree.h"

int type_name_check(char *ptr)
{
    int i, j;
    static const char reserved_words[3][BUFSIZE][MAXWORD] = {
        { "char",
        "short",
        "int",
        "long",
        "float",
        "double",
        "void",
        "" },
        { "const",
            "volatile",
            "" },
        { "printf",
            "return",
            "main",
            "continue",
            "break",
            "goto",
            "" }
    };

    for (i = 0; i < 3; i++) {
        for (j = 0; **(*(reserved_words + i) + j); j++) {
            if (!strcmp(ptr,*(*(reserved_words + i) + j)))
                return RESERVED_WORD;
        }
    }
    return NAME;
}

