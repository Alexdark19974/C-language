#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLINE 1000
enum errType { ERRNEGNIL = 1, ERRLEAPYR, ERRYR, ERRDAY, ERRMTH};
int get_line(char *, int);
int day_of_year(int, int, int);
int parse_into_operands(char *, int, int *, int *, int *, int *);
void month_day(int, int, int *, int *);
void process_error(enum errType, int, int, int, int, int, int);
static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

main()
{
    enum { YEARDAY = '0', MONTHDAY = '1' };
    int opt = 0, year = 0, month = 0, day = 0, yearday = 0;
    char line[MAXLINE] = {0};
    printf("Press \"0\" to convert month and day into day of year\n");
    printf("Press \"1\" to convert day of year into month and day\n"); 
    printf("Example:\n month and day into day of year: 1988, 12, 31\n day of year into month and day: 1988, 354\n : ");
    if (((opt = getchar()) != '0') && opt != '1')
        return printf("Error: illegal argument.\n");
    getchar();
    printf("Enter the data as 1 line: ");
    get_line(line, MAXLINE);
    if (!*line || *line == '\n')
        return printf("Zero input.\n");
    if (parse_into_operands(line, opt, &year, &yearday, &month, &day))
        return printf("Error in parsing operands\n");
    switch (opt) {
    case YEARDAY:
        printf("yearday is %d\n", day_of_year(year, month, day));
        break;
    case MONTHDAY:
        month_day(year, yearday, &month, &day);
        printf("month = %d and day = %d\n", month, day);
        break;
    default:
        printf("Unknown option.\n");
        break;
}
    return 0;
}

/* day_of_year:  set day of year from month & day */
int day_of_year(int year, int month, int day)
{
    int i, leap;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    for (i = 1; i < month; i++)
        day += (leap == 0) ? *(*daytab + i) : *(*daytab + 13 + i);
    return day;
}

/* month_day:  set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    for (i = 1; yearday > (leap == 0 ? *(*daytab + i) : *(*(daytab + leap) + i)); i++)
        yearday -= ((leap == 0) ? *(*daytab + i) : *(*(daytab + leap) + i));
    *pmonth = i;
    *pday = yearday;
}

int get_line(char *s, int lim)
{
    int i, c = 0;

    for (i = 0; (i < lim) && ((c = getchar()) != EOF) && (c != '\n'); ++i)
        *(s + i) = c;
    if (c =='\n')
        *(s + i) = c, i++;

    *(s + i) = '\0';
    return c == EOF ? EOF : i;
}

int parse_into_operands(char *line, int opt, int *pyear, int *pyearday, int *pmonth, int *pday)
{
    enum errType err;
    char delim[] = " ";
    char *ptr = NULL;
    char leap = 0;
    ptr = strtok(line, delim);
    if ((*pyear = atoi(ptr)) <= 0 && (err = ERRNEGNIL)) goto error;
    leap = *pyear%4 == 0 && *pyear%100 != 0 || *pyear%400 == 0;

    while ((ptr = strtok(NULL, delim))) {
        if (opt == '0' && !*pmonth) {
            if ((*pmonth = atoi(ptr)) <= 0 && (err = ERRNEGNIL)) goto error;
            else if (*pmonth > 12 && (err = ERRMTH)) goto error;
        }
        else if (opt == '0' && !*pday) {
            if ((*pday = atoi(ptr)) <= 0 && (err = ERRNEGNIL)) goto error;
            else if (*pday > (leap == 0 ? *(*daytab + *pmonth) : *(*(daytab + 1) + *pmonth)) && (err = ERRDAY)) goto error;
        }
        else if (opt == '1' && ((*pyearday = atoi(ptr)) <= 0) && (err = ERRNEGNIL)) goto error;
        else if (opt == '1' && leap && *pyearday > 366 && (err = ERRLEAPYR)) goto error;
        else if (opt == '1' && !leap && *pyearday > 365 && (err = ERRYR)) goto error;
    }
    if (opt == '0' && (!*pyear || !*pday || !*pmonth) && (err = ERRNEGNIL)) goto error;
    else if (opt == '1' && (!*pyear || !*pyearday) && (err = ERRNEGNIL)) goto error;
    return 0;
error:
    process_error(err, opt, *pyear, *pyearday, *pmonth, *pday, leap);
    return -1;
}

void process_error(enum errType err, int opt,  int year, int yearday, int month, int day, int leap)
{
    switch(err)
    {
        case ERRNEGNIL:
            if (opt == '0')
            printf("negative or zero value is not acceptable. Parameters: year=%d, month=%d, day=%d, leap=%d\n", year, month, day, leap);
            else
            printf("negative or zero value is not acceptable. Parameters: year=%d, yearday=%d, leap=%d\n", year, yearday, leap);
            break;
        case ERRDAY:
            printf("the day %d of month %d is illegal. MAX is %d\n", day, month, leap == 0 ? *(*daytab + month) : *(*(daytab + leap) + month));
            break;
        case ERRMTH:
            printf("month %d is illegal.\n", month); 
            break;
        case ERRYR:
            printf("a year is 365 days; your yearday is %d.\n", yearday); 
            break;
        case ERRLEAPYR:
            printf("a leap year is 366 days, your yearday is %d\n", yearday); 
            break;
        default:
            break;
    }
}
