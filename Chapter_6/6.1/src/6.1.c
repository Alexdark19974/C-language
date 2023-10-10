#include "wordcount.h"

/* count C words */
main()
{
#ifndef STRUCTPTR
    int n;
#endif
    char word[MAXWORD];
#ifdef STRUCTPTR
    struct key *p;
#endif
    struct key keytab[] = {
        { "auto", 0},
        { "break", 0},
        { "case", 0},
        { "char", 0},
        { "const", 0},
        { "continue", 0},
        { "default", 0},
        { "define", 0},
        { "double", 0},
        { "else", 0 },
        { "float", 0},
        { "if", 0},
        { "int", 0},
        { "include", 0},
        { "long", 0},
        { "signed", 0},
        { "undef", 0},
        { "unsigned", 0},
        { "void", 0},
        { "volatile", 0},
        { "while", 0},
    };
#define NKEYS (int)(sizeof(keytab) / sizeof(keytab[0]))

    while((getword(word, MAXWORD)) != EOF)
        if (isalpha(word[0]))
#ifndef STRUCTPTR
            if ((n = binsearch(word, keytab, NKEYS)) >= 0)
                keytab[n].count++;
#else
            if ((p = binsearch(word, keytab, NKEYS)) != NULL)
                p->count++;
#endif
#ifndef STRUCTPTR
    for (n = 0; n < NKEYS; n++)
        if (keytab[n].count > 0)
            printf("%4d %s\n",
                    keytab[n].count, keytab[n].word);
#else
    for (p =keytab; p < keytab + NKEYS; p++)
        if (p->count > 0)
            printf("%4d %s\n", p->count, p->word);
#endif
    return 0;
}

