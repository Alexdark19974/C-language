#include "bintree.h"

int check_if_noise_word(char *ptr)
{
    unsigned long i;
    static const char noise_words[][BUFSIZE] = 
    {
        "and",
        "the",
        "a",
        "an",
        "but",
        "or",
        "of",
        "to"
    };

    for (i = 0; i < (sizeof(noise_words) / sizeof(noise_words[0])); i++) {
        if (!strcmp(ptr, noise_words[i]))
            return NOISE_WORD;
    }

    return OK;
}

