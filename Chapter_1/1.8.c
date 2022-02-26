#include <stdio.h>
int main(void)
{
    int space_count = 0;
    int tabulation = 0;
    int EOS = 0;
    int symbol = 0;
    while((symbol = getchar()) != EOF)
    {
        if(symbol == ' ')
        {
            space_count++;
        }
        else if(symbol == '\t')
        {
            tabulation++;
        }
        else if(symbol == '\n')
        {
            EOS++;
        }
    }
    printf("space_count = %d\ntabulation = %d\nEOS = %d\n", space_count, tabulation, EOS);
    return 0;
}