#include <stdio.h>
#include <string.h>
#include <ctype.h>
enum Case { TOLOWER  = 1, TOUPPER, UNKNOWN };

main(int argc, char **argv) /* lower: convert input to lower case */
{
    int c, len = strlen(argv[0]) - 1;
    enum Case reg = UNKNOWN;

    for (; len > 0; len--)
    {
        if (argv[0][len] == '/')
            if (!strcasecmp(&argv[0][len + 1], "toupper")) {
                reg = TOUPPER;
                break;
            }
    }

    if (reg == TOUPPER) {
        while((c = getchar()) != EOF)
            putchar(toupper(c));
    }
    else if (reg == TOLOWER) {
        while((c = getchar()) != EOF)
            putchar(tolower(c));
    } else printf("Unknown option = %s.\n", &argv[0][len + 1]);

    return 0;
}

