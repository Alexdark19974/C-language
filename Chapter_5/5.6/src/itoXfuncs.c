#include "5.6.h"

int _atoi(char *s)
{
    int n = 0, sign;
    while (isspace(*s)) s++;

    sign = (*s == '-') ? -1 : 1;

    if (*s == '+' || *s == '-') s++;

    while (isdigit(*s)) n = 10 * n + (*s++ - '0');
    return sign * n;
}
int itoa(int num ,char *str)
{
    static int i = 0, sign = 0;

    if (num < 0 && sign == 0 && (sign = num)) {
        if (num == INT_MIN)
            num++;
        num = -num;
    }

    if (num / 10) {
        *(str + i) = num % 10 + '0';
        i++;
        itoa(num / 10, str);
    }
    else {
        *(str + i) = num % 10 + '0';
        i++;
        if (sign < 0) {
            *(str + i) = '-';
            i++;
        }
        *(str + i) = '\0';
        reverse(str);
        if (sign == INT_MIN)
            *(str + (i - 1)) = *(str + (i -1)) + 1;
        sign = i = 0;
    }
    return 0;
}

void reverse(char *s)
{
    static int c = 0, i = 0, j = 0;

    if (!j)
        j = strlen(s) - 1;
    if (i < j) {
        c = *(s + i), *(s + i) = *(s + j), *(s + j) = c;
        i++, j--;
        reverse(s);
    }
    c = i = j = 0;
}
