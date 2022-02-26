 
#include <stdio.h>
#define MAXS 1000
#define F_TRIGGER 6
#define TAB 8

int
get_line(char[], int);
void fold (char[], char[]);

int main (void)
{
    char string[MAXS];
    char f_string[MAXS];
    int length = 0;

    while ((length = get_line(string, MAXS)) > 0)
    {
        fold(f_string, string);
        printf("%s", f_string);
    }
    return 0;
}

int get_line(char string[], int maxs)
{
    int i = 0;
    int c;
    int tab_count = 0;

    while (i < maxs - 2 && (c = getchar()) != EOF && c != '\n')
    {
        if (c == '\t')
        {
            int res = TAB - (tab_count % TAB);

            while (res > 0)
            {
                string[i] = ' ';
                i++;
                res--;
            }
            tab_count = 0;
        }
        else
        {
            string[i] = c;
            i++;
            tab_count++;
        }
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

    while (from[i] != '\0')
    {
        if (pos >= F_TRIGGER)
        {
            if (from[i] != ' ')
            {
                if (b_pos == 0)
                {
                    b_pos = F_TRIGGER;

                    while (j < b_pos)
                    {
                        to[j] = from[j];
                        j++;
                    }
                    to[j] = '\n';
                    j++;
                    to[j] = from[b_pos];
                    j = b_pos + 1;
                    i = b_pos;
                    pos = 0;
                    b_pos = 0;
                }
                else
                {
                    while (j < b_pos)
                    {
                        to[j] = from[j];
                        j++;
                    }
                    to[b_pos] = '\n';
                    pos = 0;
                    i = b_pos + 1;
                    j = b_pos + 1;
                }
            }
            else
            {
                b_pos = i;
                
                while (j < b_pos)
                {
                    to[j] = from[j];
                    j++;
                }
                to[b_pos] = '\n';
                pos = 0;
                i = b_pos + 1;
                j = b_pos + 1;
            }
        }
        if (from[i] == ' ')
        {
            b_pos = i;
        }
        else if (from[i] == '\n')
        {
          while (j <= i)
                {
                    to[j] = from[j - 1];
                    j++;
                }    
        }
        i++;
        pos++;
    }
    to[j] = '\n';
    j++;
    to[j] = '\0';
}
