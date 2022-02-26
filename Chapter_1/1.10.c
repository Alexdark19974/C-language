#include <stdio.h>
int main(void)
{
    int c;
    while((c = getchar()) != EOF)
    {

        if(c == '\t')
        {
            printf("\\t");
        }
        else if(c == '\b')
        {
            printf("\\b");
        }
        else if(c == '\\')
        {
            printf("\\\\");
        }
        else if(c == ' ')
        {
            printf(" ");
        }
        putchar(c);
    }
    return 0;
}