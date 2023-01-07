#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>
#define MAXLINE 1000
#define ERR -1
int get_line(char line[], int lim);
int atoi(char s[]);
void itoa(int n, char s[], int field);
void reverse(char s[]);

main()
{
    int len, n, is_ready, field;
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

    field = is_ready = 0;;
    for (len = 0; len < MAXLINE; ++len)
        line[len] = 0;
    printf("Enter the number: ");
    while ((len = get_line(line, MAXLINE)) > 0) {
        if (len > 0) {
            if (!is_ready)
                n = atoi(line);
            else if (is_ready == 1) {
                field = atoi(line);
                if (field <= 0)
                    printf("error: field can't be less than or equal to 0\n");
                else {
                    itoa(n, line, field);
                    printf("itoa'ed line: %s with field=%d\n", line, field);
                }
                is_ready = -1;
            }
        }
        ++is_ready;
        if (!is_ready) {
            printf("Enter the number: ");
        }
        else if (is_ready == 1)
            printf("Enter the field width: ");
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
void itoa(int n, char s[], int field)
{
    int i, sign;

    i = 0;

    if (n < 0)
        field++;

    while (field) {
        s[i++] = '_';
        field--;
    }
    s[i--] = '\0';

    if ((sign = n) < 0) { /* record sign */
        if (n == INT_MIN) {
            n++; sign = n - 1;
        }
        n = -n;          /* make n positive */
    }

    do {        /* generate digits in reverse order */
        s[i--] = n % 10 + '0';  /* get next digit */
    } while (i >= 0 && (n /= 10) > 0);     /* delete it */

    if (sign < 0)
        s[i++] = '-';
    if (sign == INT_MIN) {
        i = strlen(s) - 1;
        s[i] = s[i] + 1;
    }
}

/* reverse:  reverse string s in place */
void reverse(char s[])
{
    int c, i, j;

    for (i = 0, j = strlen(s)-1; i < j; i++, j--)
        c = s[i], s[i] = s[j], s[j] = c;
}

