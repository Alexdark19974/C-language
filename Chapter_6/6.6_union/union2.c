#include <stdio.h>
#include <stdlib.h>
#define DISPLAY_FLOAT_INT(arg) printf("u.f=%f, float interpreted as int is depicted as u.i=%d\n", arg.f, arg.i);
typedef union Union {
    int i;
    float f;
} Union;

int main(void)
{
    Union u = {0};
    u.f = 123.5;
    DISPLAY_FLOAT_INT(u);

    return EXIT_SUCCESS;
}
