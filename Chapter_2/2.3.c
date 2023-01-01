#include <stdio.h>
#define MAXLINE 1000
int get_line(char line[], int maxline);
int htoi(char src[]);
int power(int base, int n);
int lower(int c);
int str_len(char s[]);
char is_digit(int c);
char is_hex(int c);

main ()
{
    int len, num;
    char line[MAXLINE];

    for (num = 0; num != MAXLINE; ++num)
        line[num] = 0;

    while ((len = get_line(line, MAXLINE)) > 0)
        if (len > 0) {
            num = htoi(line);
            if (num != -1) 
                printf("from hexidecimal to decimal system: %d\n", num);
            else
                printf("incorrect input data format: %s", line);
        }

    return 0;
}

int get_line(char line[], int lim)
{
    int c, i;

    c = 0;
    for (i=0;i<lim-1 && (c = getchar())!=EOF && c!='\n'; ++i)
        line[i] = c;

    if (c == '\n') {
        line[i] = c;
        ++i;
    }
    line[i] = '\0';
    return i;
}

int htoi(char src[])
{
    int i, j, num, base_ctr;
    char mv_flag;

    mv_flag = num = 0;

    i = str_len(src);
    if (src[i - 1] == '\n')
        --i;
    if (!mv_flag)
        base_ctr = i - 1;
    for (j = 0; j != i; ++j) {
        src[j] = lower(src[j]);
        if ((src[j] == '0') && lower(src[j + 1]) == 'x') {
            mv_flag = 1;
            base_ctr = i - 2 - 1;
        }
        if (mv_flag) {
            j+=1; mv_flag = 0;
        }
        else {
            if (is_digit(src[j])) {
                num = num + ((src[j] - '0') * power(16, base_ctr));
            }
            else if (is_hex(src[j])) {
                num = num + (src[j] - 97) + (10 * power(16, base_ctr));
            }
            --base_ctr;
        }
    }

    return num;
}

/* strlen: return length of s */
int str_len(char s[])
{
    int i;

    i = 0;
    while(s[i] != '\0')
        ++i;
    return i;
}

/* lower: convert c to lower case; ASCII only */
int lower(int c)
{
    if (c >= 'A' && c <= 'Z')
        return c + 'a' - 'A';
    else
        return c;
}

/* power: raise base to n-th power; n>=; version 2 */
int power(int base, int n)
{
    int p;
    if (!n)
        return 1;

    for (p = 1; n > 0; --n)
        p = p * base;
    return p;
}

char is_digit(int c)
{
    return c >= '0' && c <= '9';
}

char is_hex(int c)
{
    /*
     * since lower() converts uppercase letters into lowercase letters,
     * we might omit checking the range of 'A' && 'F'
     * But i will just leave because I like the way it looks.
     * */
    return (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
}

