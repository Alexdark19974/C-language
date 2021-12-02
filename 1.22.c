#include <stdio.h>
#define MAXS 1000
#define F_TRIGGER 6
#define TAB 8

int get_line(char[], int);
void fold (char[], char[]);

int main (void)
{
    char string[MAXS];
    char f_string[MAXS];
    int length = 0;

    while ((length = get_line(string, MAXS)) > 0)
    {
        fold (f_string, string);
        printf("%s", f_string);
    }
    return 0;
}

int get_line(char string[], int maxs)
{
    int i = 0;
    int c;

    while (i < maxs - 2 && (c = getchar()) != EOF && c != '\n')
    {
        string[i] = c;
        i++;
    }
    if (c == '\n')
    {
        string[i] = c;
    }
    i++;
    string[i] = '\0';

    return i;    
}

void fold(char to[], char from[])
{
    int i = 0;
    int j = 0;
    int pos = 0;
    int b_pos = 0;
    int b_previous = 0;
    int first_blank = 0;

    while (from[j] != '\0')
    {
         if (pos == F_TRIGGER)
         {
             if (from[j] != ' ')
             {
                while (from[j] != ' ')
                {
                     to[i] = from[j];
                     i++;
                     j++;
                }
            }
            to[b_pos] = '\n';
            pos = 0;
        }
            to[i] = from[j];
            
            if (from[j] == ' ' && from[j] != '\n')
            {
                b_pos = j;   
                // 3 7 13 16 20   16 - 3 = 13 
               // printf("%d ", b_pos);
            }
             i++, j++, pos++;
    }
    to[i] = '\0';
}