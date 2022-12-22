#include <stdio.h>

#define IN  1   /* inside a word */
#define OUT 0   /* outside a word */

/* count lines, words, and characters in input */
main()
{
    int c, nl, nw, nc, state;
    state = OUT;
    nl = nw = nc = 0;
    while ((c = getchar ()) != EOF) {
        ++nc;
        if (c == '\n')
            ++nl;
        if (c == ' ' || c == '\n' || c == '\t')
            state = OUT;
        else if (state == OUT) {
            state = IN;
            ++nw;
        }     
    }
    printf("%d %d %d\n", nl, nw, nc);
}

/*
 * bug 1: one character, i.e 'f' does not constitue a word, therefore it may be considered a bug.
 * bug 2: There is a difference between 'a' as an article and 'a' as a single non-sensical character.
 * */
