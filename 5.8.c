#include <stdio.h>

static char daytab[2][13] = 
{    
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year (int, int, int);
void month_day (int, int, int*, int*);

/*there is no error-checking in day_of_year or month_day. Remedy this defect.*/

int main(void)
{
    int year = 0;
    int month = 0;
    int day = 0;
    int p_month = 0;
    int p_day = 0;
    int yearday = 0;

    printf("insert year, month and day: "); 

    scanf ("%d %d %d", &year, &month ,&day);
    
    yearday = day_of_year(year, month, day);

    if (!yearday)
    {
        return EOF;
    }

    printf ("the day of the year is %d\n", yearday);

    month_day(year, yearday, &p_month, &p_day);

    printf ("the month and the day of the year is %i : %i\n", p_month, p_day);

    return 0;
}

int day_of_year (int year, int month, int day)
{
    int i = 0;
    int leap = 0;
    int mark = 0;

    if (year <= 0)
    {
        year = 0;
        printf("error: you have inserted the invalid number of the year.\n");
    }
    if (month > 12 || month <= 0)
    {
        month = 0;
        printf("error: you have inserted the invalid number of the month.\n");
    }
    if (day > 31 || day <= 0)
    {
        day = 0;
        printf("error: you have inserted the invalid number of the day.\n");
    }
    if (!year || !month || !day)
    {
        return 0;
    }

    ((leap = year % 4 == 0) && year % 100 != 0) || (year % 400 == 0);
    //leap = 0 == 0 -> TRUE(1)                     TRUE(1)

    for (i = 1; i < month; i++) // i < 6
    {
        day += daytab[leap][i]; // 30 + 31 + 29 + 31 + 30 + 31 = 182
    }
    return day;
}

void month_day (int year, int yearday, int *p_month, int *p_day)
{
    int i = 0;
    int leap = 0;

    ((leap = year % 4 == 0) && year % 100 != 0) || (year % 400 == 0);
    // leap = 2 == 0 -> FALSE || FALSE
    // leap = 0 == 0 -> TRUE(1)

    for (i = 1; yearday > daytab[leap][i]; i++) //182
    {
        yearday -= daytab[leap][i];
        // 182 - 31 - 29 - 31 - 30 - 31 = 30
    }   // 30 < 31
    *p_month = i; // 6
    *p_day = yearday; //30
}
