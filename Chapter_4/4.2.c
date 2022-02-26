#include <stdio.h>
#include <ctype.h>
#define MAX 1000

double atof (char[]);
int atoi (char[], int);
double my_pow (double, int);

int main(void)
{
    char s[MAX] = "123.45e-6";
    printf("%.8lf\n", atof(s));
    return 0;
}

double atof (char s[])
{
    double val = 0.0;
    double power = 1.0;
    int i = 0;
    int sign = 0;
    double exponent = 0;
    int exp_sign = 0;
    int to_the_power_of = 0;
    
    for (i = 0; isspace(s[i]); i++)
    {
        ;
    }

    sign = (s[i] == '-') ? -1 : 1;

    if (s[i] == '+' || s[i] == '-')
    {
        i++;
    }

    for (val = 0.0; isdigit(s[i]); i++)
    {
        val = 10.0 * val + (s[i] - '0');
    }

    if (s[i] == '.')
    {
        i++;
    }

    for (power = 1.0; isdigit(s[i]); i++)
    {
        val = 10.0 * val + (s[i] - '0');
        power *= 10; 
    }

    if (s[i] == 'e' || s[i] == 'E')
    {
        i++;
        exp_sign = (s[i++] == '-') ? -1 : 1; 
        to_the_power_of = atoi(s,i);
        exponent = my_pow(10.0, (exp_sign * to_the_power_of));
    }
    return (sign * (val / power)) * exponent;
}

int atoi (char s[], int n)
{
    int i = 0;
    int val = 0;

    for (i = n; s[i] != '\0'; i++)
    {
        val = 10 * val + (s[i] - '0');
    }
    return val;
}

double my_pow (double exp, int power)
{
    double i = 1.0;

    if (power < 0)
    {
        for (i = i; power < 0.0; power++)
        {
            i /= exp;
        }
    }
    else
    {
        for (i = exp; power > 0; power--)
        {
            i *= i;
        }
    }
    return i;
}