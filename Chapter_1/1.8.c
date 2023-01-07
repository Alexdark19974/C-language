#include <stdio.h>

/* count lines in input */
main()
{
    int c, nl, tb, bl;
    nl = 0; // assign '0' so as not to deal with uninitialized variables; Try it for yourself.
    tb = 0;
    bl = 0;
    while ((c = getchar()) != EOF) {
        if (c == ' ')
            bl++;
        if (c == '\t')
            tb++;
        if (c == '\n')
            nl++;
        printf("ASCI char: %d\n", c);
    }
    printf("bls = %d\ntabs = %d\nnls = %d\n", bl, tb, nl);
}

