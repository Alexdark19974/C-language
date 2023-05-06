#include "declaration.h"

int print_error(char *str, int val) 
{
    extern int tokentype;
    extern jmp_buf env;
    if (val != -1)
        printf("%s", str);
    else
        printf("%s:%c", str, val);
    longjmp(env, ERR);
}
