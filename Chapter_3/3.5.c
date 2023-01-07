#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>
#define MAXLINE 1000
#define ERR -1
#define HEX 16
#define OCTAL 8
#define BIN 2
int get_line(char line[], int lim);
int atoi(char s[]);
int power(int base, int n);
void itooc(int n, char s[]);
void itob(int n, char s[], int b);
void itoh(int n, char s[]);
void itobin(int n, char s[]);
void reverse(char s[]);

/*
 * The conversion of integer to binary, octal and hexidecimal base system, both signed and unsigned
 * */

main()
{
    int len, n, b;
    char line[MAXLINE], is_ready;

    for (len = 0; len < MAXLINE; ++len)
        line[len] = 0;
    is_ready = 0;
    printf("Enter the number: ");
    while ((len = get_line(line, MAXLINE)) > 0) {
        if (len > 0) {
            switch(is_ready) {
                case 0:
                    n = atoi(line);
                    printf("atoi'ed number=%d\n", n);
                    break;
                case 1:
                    b = atoi(line);
                    printf("atoi'ed base=%d\n", b);
                    itob(n, line, b);
                    printf("itob'ed line: %s\n", line);
                    is_ready = -1;
                    break;
                default:
                    is_ready = -1;
                    break;
            }
            is_ready++;
        }
        if (!is_ready)
            printf("Enter the number: ");
        else
            printf("Enter the base: ");
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

void itob(int n, char s[], int b)
{
    switch (b) {
        case HEX:
            itoh(n, s);
            printf("Converted into hexidecimal system: %s\n", s);
            break;
        case BIN:
            itobin(n, s);
            printf("Converted into binary system: %s\n", s);
            break;
        case OCTAL:
            itooc(n, s);
            printf("Converted into octal system: %s\n", s);
            break;
        default:
            printf("error: unknown base\n");
    }
}

void itoh(int n, char s[])
{
    char hex_table[HEX + 1] = "0123456789ABCDEF";
    int i, sign;

    strcpy(s, "0x");
    i = 2;

    if ((sign = n) < 0) {
        itobin(n, s);
        s[1]= 'x';
        printf("binary: %s\n", s);
    }
    else {
        do {
            s[i] = n % HEX;
            s[i] = hex_table[(int)s[i]]; 
            i++;
        } while ((n /= HEX) > 0);
        s[i] = '\0';
    }

    if (sign >= 0)
       reverse(s + 2);
    else {
        char sec, tmp;
        int len, j;

        for (sec = 0, tmp = 0, len = strlen(s) -1, j = 2, i = 2; i <= len; ++i) {
            if (sec != 3) {
                tmp = tmp + ((s[i] - '0') * power(2, 3 - sec));
                ++sec;
            }
            else {
                tmp = tmp + ((s[i] - '0') * power(2, 3 - sec));
                s[j] = hex_table[(int)tmp];
                j++; sec = 0; tmp = 0;
            }
        }
        s[j] = '\0';
    }
}

/* power: raise base to n-th power; n>=0; version 2 */
int power(int base, int n)
{
    int p;

    if (!n)
        return 1;
    for (p = 1; n > 0; --n)
        p = p * base;
    return p;
}

void itobin(int n, char s[])
{
    int i, sign, len;

    strcpy(s, "0b00000000000000000000000000000000");

    len = strlen(s) - 1;
    i = len;

    if ((sign = n) < 0)
        n = -n;

    do {
        if (n % 2)
             s[i] = '1';
        else
             s[i] = '0';
        i--;
    } while ((n /= BIN) > 0);

    if (sign < 0) {
        for (i = len; i > 2; --i) {
            if (s[i] == '0')
                s[i] = '1';
            else
                s[i] = '0';
        }

        i = len;

        if (s[i] == '0')
            s[i] = '1';
        else {
            do {
                s[i]= '0';
                i--;
            }
            while (s[i] != '0' && i > 2);
            s[i] = '1';
        }
        s[2] = '1';
    }
}

void itooc(int n, char s[])
{
    int i, sign, len;
    char octal_table[OCTAL] = "01234567";

    strcpy(s, "0o");
    if ((sign = n) < 0) {
        itobin(n, s);
        s[1]= 'o';
        printf("binary: %s\n", s);
    }
    else {
        i = 2;
        do {
            s[i] = n % OCTAL;
            s[i] = octal_table[(int)s[i]];
            i++;
        } while ((n /= OCTAL) > 0);
        s[i] = '\0';
    }

    if (sign >= 0)
        reverse(s + 2);
    else {
        char sec, tmp;
        int len, j;

        for (sec = 2, tmp = 0, len = strlen(s) -1, j = 2, i = 2; i <= len; ++i) {
            if (sec != 2) {
                if (i == len) {
                    tmp = tmp + ((s[i] - '0') * power(2, 0));
                    s[j] = octal_table[(int)tmp];
                    j++;
                }
                else {
                    tmp = tmp + ((s[i] - '0') * power(2, 2 - sec));
                    ++sec;
                }
            }
            else {
                tmp = tmp + ((s[i] - '0') * power(2, 2 - sec));
                s[j] = octal_table[(int)tmp];
                j++; sec = 0; tmp = 0;
            }
        }
        s[j] = '\0';
    }
}

/* reverse:  reverse string s in place */
void reverse(char s[])
{
    int c, i, j;

    for (i = 0, j = strlen(s)-1; i < j; i++, j--)
        c = s[i], s[i] = s[j], s[j] = c;
}

