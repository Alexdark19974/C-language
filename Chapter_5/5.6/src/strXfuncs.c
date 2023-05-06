#include "5.6.h"

char *_strncat(char *dest, char *src, unsigned int nbytes)
{
    char *tmp = dest;
    int i = 0;
    while (*tmp) tmp++;
    while ((*tmp++ = *src++) && ++i && --nbytes);
    *(tmp + i) = '\0';
    return dest;
}

/* strcmp:  return <0 if s < t, 0 if s==t, >0 s>t */
int _strncmp(char *s, char *t, unsigned int nbytes)
{
   while (*s++ == *t++ && --nbytes) ;
   return  nbytes == 0 ? 0 : *s - *t;
}

char *_strncpy(char *dest, char *src, unsigned int nbytes)
{
    int i = 0;
    char *tmp = dest;
    while ((*tmp++ = *src++) && ++i && --nbytes) ;
    dest[i] = '\0';
    return dest;
}

int strend(char *s, char *t)
{
    int len1 = 0, len2 = 0;
    while(*s) len1++, s++;
    while(*t) len2++, t++;
    while (*t-- == *s-- && (--len2 > 0 && --len1 > 0)) ;
    return len2 <= 0 ? 1 : 0;
}

int strindex(char *src, char *pattern)
{
    int i = 0;
    char *tmp1 = src;
    char *tmp2 = pattern;

    while (*tmp1 != '\0') {
        while (*tmp2 && *tmp1++ == *tmp2++) ;
        if (*tmp2 == '\0') return i;
        else
            tmp2 = pattern;
        i++;
    }

    return -1;
}
