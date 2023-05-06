#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#define MAXLINE 1000

int get_line(char *, int);
char *_strncat(char *, char *, unsigned int n);
char *_strncpy(char *, char *, unsigned int n);
int _strncmp(char *, char *, unsigned int n);
int strend(char *, char *);
void display_options(void);

main()
{
    enum { STRNCAT = '1', STRNCPY, STRNCMP };
    char str1[MAXLINE] = {0};
    char str2[MAXLINE * 2] = "I am a string";
    char buf[MAXLINE] = {0};
    int opt = 0;
    unsigned int nbytes = 0;
try_again:
    display_options();
    while ((opt = getchar()) != EOF) {
        getchar();
        if (opt == '0' || !isdigit(opt))
            goto exit;
        printf("Enter the string: ");
        if (get_line(str1, MAXLINE) != EOF) {
            printf("Enter the n bytes: ");
            if (get_line(buf, MAXLINE))
                goto exit;
            nbytes = atoi(buf);
            if (!nbytes) {
                printf("error: failed to perform atoi() on buf=%s\n", buf);
                goto try_again;
            }
            else if (nbytes == UINT_MAX)
                printf("WARNING: conversion of negative value in unsigned int resulted in UINT_MAX\n");
        }
        else
            opt = EOF;
        switch(opt) {
            case STRNCAT:
                _strncat(str2, str1, nbytes);
                printf("strncat=%s", str2);
                break;
            case STRNCPY:
                _strncpy(str2, str1, nbytes);
                printf("strncpy=%s", str2);
                break;
            case STRNCMP:
                if (!_strncmp(str2, str1, nbytes))
                    printf("the lines equal\n");
                else
                    printf("the lines are not equal\n");
                break;
            default:
                goto exit;
                break;
        }
        display_options();
    }
    return 0;
exit:
    printf("Normal exit.\n");
    return 0;
}

int get_line(char *s, int lim)
{
    int i, c = 0;

    for (i = 0; (i < lim) && ((c = getchar()) != EOF) && (c != '\n'); ++i)
        s[i] = c;
    if (c =='\n')
        s[i++] = c;

    s[i] = '\0';
    return c == EOF ? EOF : i;
}

char *_strncat(char *dest, char *src, unsigned int nbytes)
{
    int i = 0;
    char *tmp = dest;
    while (*tmp) tmp++;
    while ((*tmp++ = *src++) && ++i && --nbytes) ;
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

void display_options(void)
{
    printf("-----------------------------------------------\n");
    printf("0 - exit, 1 - strncat, 2 - strncpy, 3 - strncmp\n");
    printf("-----------------------------------------------\n");
    printf(": ");
}
