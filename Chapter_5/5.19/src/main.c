#include "declaration.h"
int tokentype;              /* type of last token */
char token[MAXTOKEN];       /*last token string */
char name[MAXTOKEN];        /*identifier name */
char datatype[MAXTOKEN];    /* data type = char, int, etc. */
char out[1000];             /* output string */
char parens = 0; /* find an opening bracket (TRUE), make FALSE if closing bracket met*/
int asterisk = 0, comma = 0, square_check = 0, list = 0, encapsulate = 0;
jmp_buf env;
/* undcl:  convert word description to declaration */
/* Can "ptr * x () int" be considered a word description? 
 * It's a rhetorical question for I dare not question K&R wording.
 * The current declaration constructor is a bit smarter than what is present in the book
 * It can handle declarations like:
 * 1) int * (int *ptr);
 * 2) int (*x)[15];
 * 3) int *x(int (*ptr)[15]);
 * 4) int *x(int x[15][15]);
 * And even point out various errors of different flavors;
 * It would be nice to specify where exactly in the string from input the mistake is
 * But it is a test program, not an attempt to write a monster of an analyzer,
 * Though, judging by the number of lines of code, it would seem quite the case.
 * Anyway, there may be bugs here and there; it might accept declarations that should be erroneous.
 * We can endlessly improve this program.
 * */
main(int argc, char **argv)
{
    if (argc > 1 && *++argv != NULL)
        if (!strcmp("-h", *argv) || !strcmp("--help", *argv))
            print_usage();
    if (setjmp(env) != 0) {
        gettoken(SKIP_TOKEN);
        goto try_again;
    } else
try_again:
        clear_buffers(token, name, out, datatype, NULL, NULL, NULL);
        tokentype = comma = list = asterisk = 0;
        parse();
    return 0;
}

void print_usage(void)
{
    printf("usage:\n\tinput: x * (x * int) * int\n\toutput: int * (*x)(int * x)\n");
}
