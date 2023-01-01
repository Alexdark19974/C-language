#include <stdio.h>
#include <limits.h>
#include <float.h>
#define UCHAR_MIN   0
#define USHRT_MIN   0
#define UINT_MIN    0
#define ULONG_MIN   0

void print_char_range(void);
void print_short_range(void);
void print_int_range(void);
void print_long_range(void);
void compute_ranges(void);

main()
{
    printf("Do you want to print ranges from standard libraries or by computing? 1\\0: ");
    if (getchar() == '1') {
        print_char_range();
        print_short_range();
        print_int_range();
        print_long_range();
    }
    else
        compute_ranges();

    return 0;
}

void print_char_range(void) 
{
    printf("signed char min: %d - signed char max: %d\nunsigned char min: %u - unsigned char max: %u\n --------------------------------------------\n", SCHAR_MIN, SCHAR_MAX, UCHAR_MIN, UCHAR_MAX);
}

void print_short_range(void) 
{
    printf("signed short min: %hd - signed short max: %hd\nunsigned short min: %hu - unsigned short max: %hu\n --------------------------------------------\n", SHRT_MIN, SHRT_MAX, USHRT_MIN, USHRT_MAX);
}

void print_int_range(void) 
{
    printf("signed int min: %d - signed int max: %d\nunsigned int min: %u - unsigned int max: %u\n --------------------------------------------\n", INT_MIN, INT_MAX, UINT_MIN, UINT_MAX);
}

void print_long_range(void) 
{
    printf("signed long min: %ld - signed long max: %ld\nunsigned long min: %lu - unsigned long max: %lu\n --------------------------------------------\n", LONG_MIN, LONG_MAX, ULONG_MIN, ULONG_MAX);
}

void compute_ranges(void)
{
    /*it is going to take a very very long time since values are incremented by 1 but the job will eventually be done */
    char c;
    unsigned char uc;
    short s;
    unsigned short us;
    int i;
    unsigned ui;
    long l;
    unsigned long ul;

    c = uc = s = us = i = ui = l = ul = 0;

    while (ul != ULONG_MAX) {
        if (uc != UCHAR_MAX)
            ++uc;
        if (c != CHAR_MAX)
            ++c;
        if (us != USHRT_MAX)
            ++us;
        if (s != SHRT_MAX)
            ++s;
        if (ui != UINT_MAX)
            ++ui;
        if (i != INT_MAX)
            ++i;
        if (l != LONG_MAX)
            ++l;
        ++ul;
    }

    printf("---------- UNSIGNED CHAR ----------\nnunsigned char min: %u - unsigned char max: %u\n --------------------------------------------\n", UCHAR_MIN, uc);
    printf("---------- UNSIGNED SHORT ----------\nnunsigned short min: %hu - unsigned short max: %hu\n --------------------------------------------\n", USHRT_MIN, us);
    printf("---------- UNSIGNED INT ----------\nnunsigned int min: %u - unsigned int max: %u\n --------------------------------------------\n", UINT_MIN, ui);
    printf("---------- UNSIGNED LONG ----------\nnunsigned long min: %lu - unsigned long max: %lu\n --------------------------------------------\n", ULONG_MIN, ul);
    printf("---------- SIGNED CHAR ----------\nsigned char max: %d\n --------------------------------------------\n", c);
    printf("---------- SIGNED SHORT ----------\nsigned short max: %hd\n --------------------------------------------\n", s);
    printf("---------- SIGNED INT ----------\nsigned int max: %d\n --------------------------------------------\n", i);
    printf("---------- SIGNED LONG ----------\nsigned long max: %ld\n --------------------------------------------\n", l);

    while (l != LONG_MIN) {
        if (c != CHAR_MIN)
            --c;
        if (s != SHRT_MIN)
            --s;
        if (i != INT_MIN)
            --i;
        --l;
    }
    printf("----------SIGNED CHAR -----------\nsigned char min: %d\n", c);
    printf("----------SIGNED SHORT -----------\nsigned short min: %hd\n", s);
    printf("----------SIGNED INT -----------\nsigned int min: %d\n", i);
    printf("----------SIGNED LONG -----------\nsigned long min: %ld\n", l);
}

