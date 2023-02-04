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
void printd(int n);

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
            printf("printd'ed number =");
            printd(n);
            putchar('\n');
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
    static int i = 0, sign = 0;

    /*
     * The following line is a point of failure since
     * INT_MIN = -2147483648 and INT_MAX = 2147483647
     * so signed int cannot contain 214748648
     * if attempted to convert, we will get -2147483648
     * -2147483648 % 10 + '0' = 40 = '('
     * */
    if (n < 0 && sign == 0 && (sign = n)) { /* record sign */
        if (n == INT_MIN)
            n++;
        n = -n;          /* make n positive */
    }

    if (n / 10) {
        s[i++] = n % 10 + '0';
        itoa(n / 10, s);
    }
    else {
        s[i++] = n % 10 + '0';
        if (sign < 0)
            s[i++] = '-';
        s[i] = '\0';
        reverse(s);
        if (sign == INT_MIN)
            s[i - 1] = s[i - 1] + 1;
        sign = i = 0;
    }
}

/* reverse:  reverse string s in place */
void reverse(char s[])
{
    static int c = 0, i = 0, j = 0;

    if (!j)
        j = strlen(s) - 1;
    if  (i < j) {
        c = s[i], s[i] = s[j], s[j] = c;
        i++, j--;
        reverse(s);
    }
    c = i = j = 0;
}

/* printd: print n in decimal */
void printd(int n)
{
    if (n < 0) {
        putchar('-');
        n = -n;
    }
    if (n / 10)
        printd(n / 10);
    putchar(n % 10 + '0');
}

