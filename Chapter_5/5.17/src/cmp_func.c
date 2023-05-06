#include "linesort.h"
#include <ctype.h>

/* numcmp:  compare s1 and s2 numerically */
int numcmp(const char *s1, const char *s2,  int opt)
{
    if (opt & DIRECTORY_ORDER)
        return _strcmp_directory_order(s1, s2, ~NUMERIC & opt);
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

int numncmp(const char *s1, const char *s2,  int opt, int field_length)
{
    if (opt & DIRECTORY_ORDER || opt & FIELD_LENGTH)
        return _strncmp_directory_order(s1, s2, ~NUMERIC & opt, field_length);
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

int _strncasecmp(const char *letter1, const char *letter2, int field_length) {
    while (field_length > 0 && toupper(*letter1) == toupper(*letter2)) {
        if (*letter1 == '\0')
            return 0;
        if (--field_length <= 0)
            return 0;
        letter1++, letter2++;
    }
    return toupper(*letter1) - toupper(*letter2);
}

int _strcmp_directory_order(const char *str1, const char *str2, int opt)
{
    while (1) {
        if (opt & NUMERIC && !isdigit(*str1) && *str1 != ' ')
            while(!isdigit(*str1) && *str1 != ' ' && *str1) str1++;
        if (opt & NUMERIC && !isdigit(*str2) && *str2 != ' ')
            while(!isdigit(*str2) && *str2 != ' ' && *str2) str2++;
        if (!(opt &NUMERIC) && !isalnum(*str1) && *str1 != ' ')
            while (!isalnum(*str1) && *str1 != ' ' && *str1) str1++;
        if (!(opt & NUMERIC) && !isalnum(*str2) && *str2 != ' ')
            while (!isalnum(*str2) && *str2 != ' ' && *str2) str2++;
        if (*str1 == '\0') return 0;
        if ((opt & FOLD) ? (toupper(*str1) != toupper(*str2)) : *str1 != *str2)
           break;
        str1++, str2++;
    }
    return *str1 - *str2;
}

int _strncmp_directory_order(const char *str1, const char *str2, int opt, int field_length)
{
    while (1) {
        if (opt & NUMERIC && !isdigit(*str1) && *str1 != ' ')
            while(field_length > 0 && !isdigit(*str1) && *str1 != ' ' && *str1) str1++;
        if (opt & NUMERIC && !isdigit(*str2) && *str2 != ' ')
            while(field_length > 0 && !isdigit(*str2) && *str2 != ' ' && *str2) str2++;
        if (!(opt & NUMERIC) && !isalnum(*str1) && *str1 != ' ')
            while (field_length > 0 && !isalnum(*str1) && *str1) str1++;
        if (!(opt & NUMERIC) && !isalnum(*str2) && *str2 != ' ')
            while (field_length > 0 && !isalnum(*str2) && *str2) str2++;
        if (field_length <= 0 || *str1 == '\0') return 0;
        if ((opt & FOLD) ? (toupper(*str1) != toupper(*str2)) : *str1 != *str2)
            break;
        str1++, str2++,field_length--;
    }
    return *str1 - *str2;
}

int _strcmp_ext(const char *s1, const char *s2, int field_length, enum opt opt)
{
    if (!(opt & NUMERIC) && !(opt & DIRECTORY_ORDER))
        return (opt & FOLD) ? (opt & FIELD_LENGTH) ? _strncasecmp(s1, s2, field_length) : _strcasecmp(s1, s2) : (opt & FIELD_LENGTH) ? strncmp(s1, s2, field_length) : strcmp(s1, s2);
    else if ((opt & DIRECTORY_ORDER) && !(opt & NUMERIC))
        return (opt & FIELD_LENGTH) ? _strncmp_directory_order(s1, s2, (opt & FOLD) ? FOLD : NONE, field_length) :_strcmp_directory_order(s1, s2, (opt & FOLD) ? FOLD : NONE);
    else if (opt & NUMERIC) {
        if ((opt & FOLD) || !(opt & FOLD))
            return (opt & DIRECTORY_ORDER) ? (opt & FIELD_LENGTH) ? _strncmp_directory_order(s1, s2, NUMERIC | DIRECTORY_ORDER | FIELD_LENGTH, field_length) : _strcmp_directory_order(s1, s2, NUMERIC | DIRECTORY_ORDER) : (opt & FIELD_LENGTH) ? numncmp(s1, s2, opt, field_length) : numcmp(s1, s2, opt);
    }
    return 0;
}
