#include <stdio.h>
#define FARMIN  0
#define FARMAX  300
#define STEP    20
/* create chart of farenheits to celcius and backwards*/

int fahr_to_celc(int, int, int);
/* print Fahrenheit-Celsius table 
    for fahr = 0, 20, ..., 300; floating-point version */
main()
{
    fahr_to_celc(FARMIN, FARMAX, STEP);
}

int fahr_to_celc(int lower, int upper, int step)
{
    float fahr, celsius;

    fahr = lower;
    printf("-----Fahrenheit-Celsius table-----\n");
    while (fahr <= upper) {
        celsius = (5.0/9.0) * (fahr-32.0);
        printf("%3.0f %6.1f\n", fahr, celsius);
        fahr = fahr + step;
    }
    return 0;
}

