#include <stdio.h>
#include <ctype.h>
#define LIMIT 102
/*Write the function htoi(s) which converts a string of hexadecimal digits (including an optional 0x, 0X) into its equivalent integer value. Allowable digits are 0..9, a through f, A through F.*/
void get_line (char[], int);
void htoi(char[]);
int main(void)
{
    char s[LIMIT];
    get_line(s, LIMIT);
    htoi(s);

    return 0;
}
void htoi(char s[])
{
    int i = 0;
    char map_of_hex[LIMIT] = "0123456789abcdef\0";
    int formula = 0;
    
    if (s[i] == '0' && s[i + 1] == 'x')
    {
        i++;
        i++;
        while (s[i] != '\0')
            {
                for (int j = 0; j < 16; j++)
                {
                    if (s[i] == map_of_hex[j])
                    {
                        formula = formula * 16 + j;
                        if (s[i + 1] == '\0')
                        {
                            printf("%d", formula);
                        }
                        break;
                    }
                }
                i++;
            }
    }
    else
    {
        printf("Invalid hexidecimal number\n");
            return;
    }
}

void get_line (char s[], int max)
{
    int c, i = 0;
    for (i = 0; i < LIMIT - 2 && (c = getchar()) != EOF && c != '\n'; i++)
    {
        if (c >= 'A' && c <= 'Z')
        {
            c = tolower(c);
        }
        s[i] = c;
    }
    s[i] = '\0';
    return;
}