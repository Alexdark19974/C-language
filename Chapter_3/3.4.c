#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>
#define MAXLINE 1000
#define ERR -1
int get_line(char line[], int lim);
int atoi(char s[]);
void itoa(int n, char s[]);
void reverse(char s[]);

main()
{
    int len, n;
    char line[MAXLINE];

    /*
     * Not really necessary 
     * but it is nice 
     * to have INT_MIN & INT_MAX 
     * in front of your face for 
     * simplicity's sake
     * */
    printf("INT MIN=%d\n", INT_MIN);
    printf("INT MAX=%d\n", INT_MAX);
    for (len = 0; len < MAXLINE; ++len)
        line[len] = 0;
    printf("Enter the line: ");
    while ((len = get_line(line, MAXLINE)) > 0) {
        if (len > 0) {
            n = atoi(line);
            printf("atoi'ed number=%d\n", n);
            itoa(n, line);
            printf("itoa'ed line: %s\n", line);
        }
        printf("Enter the line: ");
    }

    return 0;
}

int get_line(char line[], int lim)
{
    int i, c;

    c = 0;
    for (i=0;i<lim-1 && (c = getchar())!=EOF && c!='\n'; ++i)
        line[i] = c;

    if (c == '\n')
        line[i++] = c;

    line[i] = '\0';
    return i;
}

/* atoi:  convert s to integer; version 2 */
int atoi(char s[])
{
    int i, n, sign;

    for (i = 0; isspace(s[i]); i++)  /* skip white space */
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')  /* skip sign */
        i++;
    for (n = 0; isdigit(s[i]); i++)
        n = 10 * n + (s[i] - '0');
    return sign * n;
}

/* itoa:  convert n to characters in s */
void itoa(int n, char s[])
{
    int i, sign;

    /*
     * The following line is a point of failure since
     * INT_MIN = -2147483648 and INT_MAX = 2147483647
     * so signed int cannot contain 214748648
     * if attempted to convert, we will get -2147483648
     * -2147483648 % 10 + '0' = 40 = '('
     * */
    if ((sign = n) < 0) { /* record sign */
        if (n == INT_MIN) {
            n++; sign = n - 1;
        }
        n = -n;          /* make n positive */
    }
    i = 0;
    do {        /* generate digits in reverse order */
        s[i++] = n % 10 + '0';  /* get next digit */
    } while ((n /= 10) > 0);     /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
    if (sign == INT_MIN)
        s[i - 1] = s[i - 1] + 1;
}

/* reverse:  reverse string s in place */
void reverse(char s[])
{
    int c, i, j;

    for (i = 0, j = strlen(s)-1; i < j; i++, j--)
        c = s[i], s[i] = s[j], s[j] = c;
}

