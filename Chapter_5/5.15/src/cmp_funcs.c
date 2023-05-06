#include "linesort.h"

/* numcmp:  compare s1 and s2 numerically */
int numcmp(const char *s1, const char *s2)
{
    double v1, v2;
    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

int _strcasecmp(const char *letter1, const char *letter2) {
    while (toupper(*letter1) == toupper(*letter2)) {
        if (*letter1 == '\0')
            return 0;
        letter1++, letter2++;
    }
    return toupper(*letter1) - toupper(*letter2);
}

int _strcmp_ext(const char *s1, const char *s2, enum opt opt)
{
    if (!(opt & NUMERIC))
        return (opt & FOLD) ? _strcasecmp(s1, s2) : strcmp(s1, s2);
    else if (opt & NUMERIC)
            return numcmp(s1, s2);
    return 0;
}
