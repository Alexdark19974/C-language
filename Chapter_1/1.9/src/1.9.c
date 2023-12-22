#include <stdio.h>

main (void)
{
    int c;
    int blc;

    blc = 0;
    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            if (!blc)
                printf("\' \'"); // ' ' represents one blank
            blc++;
        }
        if (c != ' ') {
            blc = 0;
            putchar(c);
        }
    }
}

