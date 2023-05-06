#include "linesort.h"
#include <ctype.h>

/* numcmp:  compare s1 and s2 numerically */
int numcmp(const char *s1, const char *s2,  int opt)
{
    if (opt & DIRECTORY_ORDER)
        _strcmp_directory_order(s1, s2, opt);
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

int _strcmp_directory_order(const char *str1, const char *str2, int opt)
{
    while (1) {
        if (opt & NUMERIC && !isdigit(*str1) && *str1 != ' ')
            while (!isdigit(*str1) && *str1 != ' ' && *str1) str1++;
        if (opt & NUMERIC && !isdigit(*str2) && *str2 != ' ')
            while (!isdigit(*str2) && *str2 != ' ' && *str2) str2++;
        if (!(opt & NUMERIC) && !isalnum(*str1) && *str1 != ' ')
            while (!isalnum(*str1) && *str1 != ' ' && *str1) str1++;
        if (!(opt & NUMERIC) && !isalnum(*str2) && *str2 != ' ')
            while (!isalnum(*str2) && *str2 != ' ' && *str2) str2++;
        if (*str1 == '\0') return 0;
        if ((opt & FOLD) ? (toupper(*str1)) != toupper(*str1) : *str1 != *str2)
            break;
    }
    return *str1 - *str2;
}

int _strcmp_ext(const char *s1, const char *s2, enum opt opt)
{
    if (!(opt & NUMERIC) && !(opt & DIRECTORY_ORDER))
        return (opt & FOLD) ? _strcasecmp(s1, s2) : strcmp(s1, s2);
    else if ((opt & DIRECTORY_ORDER) && !(opt & NUMERIC))
        return _strcmp_directory_order(s1, s2, (opt & FOLD) ? FOLD : NONE);
    else if (opt & NUMERIC) {
        if ((opt & FOLD) || !(opt & FOLD))
            return opt & DIRECTORY_ORDER ? _strcmp_directory_order(s1, s2, NUMERIC | DIRECTORY_ORDER) : numcmp(s1, s2, opt);
    }
    return 0;
}
