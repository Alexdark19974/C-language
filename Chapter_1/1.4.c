#include <stdio.h>

/* print Fahrenheit-Celsius table 
    for fahr = 0, 20, ..., 300; floating-point version */
main()
{
    float fahr, celsius;
    float lower, upper, step;

    lower = -17.8;        /* lower limit of temperature table */
    upper = 148.9;      /* upper limit */
    step = 11.1;        /* step size */

    celsius = lower;
    printf("-----Celsius-Fahrenheit table-----\n");
    while (celsius <= upper) {
        fahr = (celsius * (9.0/5.0)) + 32;
        printf("%6.1f %3.0f\n", celsius, fahr);
        celsius = celsius + step;
    }
}
