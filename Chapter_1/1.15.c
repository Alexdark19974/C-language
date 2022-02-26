#include <stdio.h>
#define FARMIN 0
#define FARMAX 300
/* create chart of farenheits to celcius and backwards*/

void conversion_f_to_c_table(void)
{
    printf("     Farenheit to Celcius and backwards\n"
    "-------------------------------------------------\n");
    for (int i = FARMIN; i <= FARMAX; i = i + 20)
    {
        double celcius  = (double) (i - 32.0) * 5.0/9.0;
        printf("| %dF:\t\t%.2lfC\t|  %.2fC:\t%dF\t|\n", i, celcius, celcius, i);
    }    
}

int main (void)
{
    conversion_f_to_c_table();
    return 0;
} 