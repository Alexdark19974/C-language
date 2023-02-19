#include "5.6.h"

main()
{
    enum { STRNCAT = '1', STRNCPY, STRNCMP, STREND, STRINDEX, ATOI, ITOA };
    char str1[MAXLINE] = {0};
    char str2[MAXLINE * 2] = "I am a string\n";
    char buf[MAXLINE] = {0};
    int opt = 0;
    unsigned int nbytes = 0;
try_again:
    display_options();
    while ((opt = getop(str1)) != EOF) {
        if (opt == '0' || !isdigit(opt))
            goto exit;
        printf("Enter the string: ");
        if (get_line(str1, MAXLINE) != EOF) {
            if (str1[0] == '\n')
                goto try_again;
            if (opt == STREND || opt == STRINDEX || opt == ATOI || opt == ITOA)
                goto _case;
            printf("Enter the n bytes: ");
            if (get_line(buf, MAXLINE) == EOF)
                goto exit;
            nbytes = _atoi(buf);
            if (!nbytes) {
                printf("error: failed to perform atoi() on buf=%s\n", buf);
                goto try_again;
            }
            else if (nbytes == UINT_MAX)
                printf("WARNING: conversion of negative value in unsigned int resulted in UINT_MAX\n");
        }
        else
            opt = EOF;
_case:
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
            case STREND:
                if (strend(str2, str1))
                    printf("str1=%s is inside str2=%s", str1, str2);
                else
                    printf("str1=%s is not inside str2=%s", str1, str2);
                break;
            case STRINDEX:
                if ((opt = strindex(str2, str1)) != -1)
                    printf("Found substring %s in %s at index=%d", str1, str2, opt);
                else
                    printf("Failed to find substring %s in %s", str1, str2);
                break;
            case ATOI:
                printf("atoi'd string %s = %d\n", str1, _atoi(str1));
                break;
            case ITOA:
                opt = _atoi(str1);
                itoa(opt, str1);
                printf("itoa'ed number = %s\n", str1);
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
        *(s + i) = c;
    if (c =='\n')
        *(s + i) = c, i++;

    *(s + i) = '\0';
    return c == EOF ? EOF : i;
}

void display_options(void)
{
    printf("---------------------------------------------------------------------------------------------\n");
    printf("0 - exit, 1 - strncat, 2 - strncpy, 3 - strncmp, 4 - strend, 5 - strindex, 6 - atoi, 7 - itoa\n");
    printf("---------------------------------------------------------------------------------------------\n");
    printf(": ");
}
