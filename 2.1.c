#include <stdio.h>
#include <limits.h>
#include <float.h>
#define BIT 8
void power_for_char(int, int);
void power_for_int(int, int);
void power_for_short(int, int);
void power_for_long (int, int);
void power_for_long_long(int, int);
int main(void)
{
    int c;
    power_for_char(2, BIT);
    power_for_int(2, BIT * sizeof(int));
    power_for_short(2, BIT * sizeof(short));
    power_for_long(2, BIT * sizeof(long));
    power_for_long_long(2, BIT * sizeof(long long));
    while ((c = getchar()) != EOF)
    {
        if (c == 'c')
        {
           printf("         char type\n");
           printf("signed from: %d to: %d\n", SCHAR_MIN, SCHAR_MAX);
           printf("unsigned from: %d to: %u\n", 0, UCHAR_MAX);
        }
        else if (c == 'i')
        {
            printf ("       int type\n");
            printf("singed from: %d to: %d\n", INT_MIN, INT_MAX);
            printf("unsigned from: %d to: %u\n", 0, UINT_MAX);
        }
        else if (c == 's')
        {
            printf ("       short type\n");
            printf("singed from: %d to: %d\n", SHRT_MIN, SHRT_MAX);
            printf("unsigned from: %d to: %u\n", 0, USHRT_MAX);
        }
        else if (c == 'l')
        {
            printf ("       long type\n");
            printf("singed from: %ld to: %ld\n", LONG_MIN, LONG_MAX);
            printf("unsigned from: %d to: %lu\n", 0, ULONG_MAX);   
        }
        else if (c == 'L')
        {
            printf ("       long long type\n");
            printf("singed from: %lld to: %lld\n", LLONG_MIN, LLONG_MAX);
            printf("unsigned from: %d to: %llu\n", 0, ULLONG_MAX);
        }
        else if (c == 'f')
        {
            printf ("       float type\n");
            printf("from: %e to: %e\n", FLT_MIN, FLT_MAX);      
        }
        else if (c == 'd')
        {
            printf ("       double type\n");
            printf("from: %e to: %e\n", DBL_MIN, DBL_MAX); 
        }
        else if (c == 'D')
        {
            printf ("       long double type\n");
            printf("from: %Le to: %Le\n", LDBL_MIN, LDBL_MAX);
        }
        else if (c == '\n')
        {
            continue;
        }
        else
        {
            printf ("wrong letter\n");
        }
    }
    return 0;
}
void power_for_char (int number, int power)
{
    int char_u = 1;
    int char_s = 1;
    for (int i = 0; i < power; i++)
    {
        char_u = char_u * number;
    }
    for (int i = 0; i < power - 1; i++)
    {
        char_s = char_s * number;
    }
    printf ("       char type\n");
    printf("from: 0 to: %d\n", char_u - 1);
    printf("from: %d to: %d\n", char_s * -1, char_s - 1);
}

void power_for_int ( int number, int power)
{
    int res = 1;
    int res_s = 1;
    for (int i = 0; i < power; i++)
    {
        res = (res * number);
    }
    for (int i = 0; i < power - 1; i++)
    {
        res_s = res_s * number;
    }
    printf ("       int type\n");
    printf("from: 0 to: %u\n", res - 1);
    printf("from: %d to: %d\n", res_s, res_s - 1);
}

void power_for_short(int number, int power)
{
    int short_u = 1;
    int short_s = 1;
    for (int i = 0; i < power; i++)
    {
        short_u = short_u * number;
    }
    for (int i = 0; i < power - 1; i++)
    {
        short_s = short_s * number;
    }
    printf ("       short type\n");
    printf("from: 0 to: %d\n", short_u - 1);
    printf("from: %d to: %d\n", short_s * -1, short_s - 1);
}
void power_for_long (int number, int power)
{
    long long_u = 1;
    long long_s = 1;
    for (int i = 0; i < power; i++)
    {
        long_u = long_u * number;
    }
    for (int i = 0; i < power - 1; i++)
    {
        long_s = long_s * number;
    }
    printf ("       long type\n");
    printf("from: 0 to: %lu\n", long_u - 1);
    printf("from: %ld to: %ld\n", long_s * -1, long_s - 1);
}
void power_for_long_long(int number, int power)
{
    long long long_long_u = 1;
    long long long_long_s = 1;
    for (int i = 0; i < power; i++)
    {
        long_long_u = long_long_u * number;
    }
    for (int i = 0; i < power - 1; i++)
    {
        long_long_s = long_long_s * number;
    }
    printf ("       long long type\n");
    printf("from: 0 to: %llu\n", long_long_u - 1);
    printf("from: %lld to: %lld\n", long_long_s * -1, long_long_s - 1);   
}