#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>
#define IS_UPPER(c) c >= 'A' && c <= 'Z'
int is_upper(int);
int _IS_func(char *, int);
void _IS_func_init(char *, char);
enum { IS_UPPER_CASE = 1, IS_LOWER_CASE = 2 };

main(int argc, char **argv)
{
    int c = 0;
    char lookup_table[UCHAR_MAX] = {0};
    char is_func = 0;

    while (--argc && *++argv && **argv == '-') {
        switch (tolower(*++*argv)) {
            case 'u':
                is_func = IS_UPPER_CASE;
                argc = 1;
                break;
            case 'l':
                is_func = IS_LOWER_CASE;
                argc = 1;
                break;
            default:
                fprintf(stderr, "unknown option = %s\n", *argv - 1);
                fprintf(stderr, "usage: ./your_program -l <-(\"is_lower()\")\n");
                exit(EXIT_FAILURE);
        }
    }
    if (!is_func) {
        printf("warning: having no args results in defaulting to \"-l (is_upper())\" mode\n");
        is_func = IS_UPPER_CASE;
    }
    _IS_func_init(lookup_table, is_func);

    while((c = getc(stdin)) > 0) {
        /* if (is_upper(c))
                printf("is an upper case.\n");
            else printf("is not an upper case.\n"); */
        // printf(is_upper(c) ? "is an upper case\n" : "is not an upper case\n");
        // printf(IS_UPPER(c) ? "is an upper case\n" : "is not an upper case\n"); // probably, the best space-saving uppercase check.
        switch (is_func) {
            case IS_UPPER_CASE:
                printf(_IS_func(lookup_table, c) ? "is an upper case\n" : "is not an upper case\n"); // probably, the best time-saving uppercase check
                break;
            case IS_LOWER_CASE:
                printf(_IS_func(lookup_table, c) ? "is an lower case\n" : "is not an lower case\n"); // probably, the best time-saving uppercase check
                break;
            default:
                printf(_IS_func(lookup_table, c) ? "is an upper case\n" : "is not an upper case\n"); // probably, the best time-saving uppercase check
                break;
        }
        getc(stdin);
    }
    return 0;
}

int is_upper(int c)
{
    return c >= 'A' && c <= 'Z'; // an even shorter version
    // return c >= 'A' && c <= 'Z' ? 1 : 0; // shorter version
    /* if (c >= 'A' && c <= 'Z')
        return 1;
       else return 0; */
    // return strchr("ABCDEFGHKLMNOPQRSTUVWXYZ", c) ? 1 : 0;
}

int is_lower(int c)
{
    return c >= 'a' && c <= 'z';
}

int _IS_func(char *lookup_table, int c)
{
    return *(lookup_table + (unsigned char)c);
}

void _IS_func_init(char *lookup_table, char is_func)
{
    int i;

    for (i = 0; i < UCHAR_MAX; i++) {
        switch(is_func) {
            case IS_UPPER_CASE:
                lookup_table[i] = is_upper(i);
                break;
            case IS_LOWER_CASE:
                lookup_table[i] = is_lower(i);
                break;
            default:
                lookup_table[i] = is_upper(i);
                break;
        }
    }
}

