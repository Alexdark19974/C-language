#include <stdio.h>
#include <ctype.h>
#define MAXLINE 1000    /* maximum input line length */

int get_line(char line[], int max);
double atof(char s[]);
double power(int base, int n);
int atoi(char s[]);
double calculate(char sign, double val, char s[]);
/* find all lines matching pattern */
main()
{
    char line[MAXLINE] = {0};
    double ret = 0;

    printf("Enter the line: ");
    while (get_line(line, MAXLINE) > 0) {
        ret = atof(line);
        printf("atof'ed line: %.12lf\n", ret);
        printf("Enter the line: ");
    }
    return 0;
}

/* getline: get line into s, return length */
int get_line(char s[], int lim)
{
    int c, i;

    i = c = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c!= '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

/* atof:  convert string s to double */
double atof(char s[])
{
    double val, power;
    int i, sign;

    for (i = 0; isspace(s[i]); i++)  /* skip white space */
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }

    val = sign * val / power;

    /* any alphabet character other than 'e'/'E' 
     * will not be taken into account 
     Let the program be strict. */
    if (s[i] == 'e' || s[i] == 'E') {
        i++;
        if (s[i] == '+' && isdigit(s[i + 1]))
            val = calculate(0, val, s + (i + 1));
        else if (s[i] == '-' && isdigit(s[i + 1]))
            val = calculate(1, val, s + (i + 1));
        else {
            goto error;
        }
    }
    return val;

error:
    printf("error: unknown symbol");
    return -1;
}

double calculate(char sign, double val, char s[])
{
    double tmp = 0.0;

    tmp = atoi(s);
    (!sign) ? tmp = power(10, tmp) : (tmp = power(10, tmp * -1));
    return  val * tmp;
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

/* power: raise base to n-th power; n>=; version 2 */
double power(int base, int n)
{
    double p;
    if (!n)
        return 1;
    if (n > 0) {
        for (p = 1; n > 0; --n)
            p*= base;
    }
    else {
        p = (double) base; n = -n;
        while (n-- > 0)
            p*=base;
        p = base / p;
    }
    return p;
}

