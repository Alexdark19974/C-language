#include "wordcount.h"

/* binsearch: find word in tab[0]...tab[n-1] */
#ifndef STRUCTPTR
int binsearch(char *word, struct key tab[], int n)
#else
struct key *binsearch(char *word, struct key *tab, int n)
#endif
{
    int cond;
#ifndef STRUCTPTR
    int low, high, mid;
#else
    struct key *low = &tab[0];
    struct key *high = &tab[n];
    struct key *mid;
#endif

#ifndef STRUCTPTR
    low = 0;
    high = n - 1;
#endif
    while (low <= high) {
#ifndef STRUCTPTR
        mid = (low + high) / 2;
#else
        mid = low + (high-low) / 2;
#endif
#ifndef STRUCTPTR
        if ((cond = strcmp(word, tab[mid].word)) < 0)
#else
        if ((cond = strcmp(word, mid->word)) < 0)
#endif
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }
#ifndef STRUCTPTR
    return -1;
#else
    return NULL;
#endif
}

