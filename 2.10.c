#include  <stdio.h>
int lower (int);
/*

*/

int main (void)
{
    int symbol = 'A';  

    printf("%c\n", lower(symbol));

    return 0;
}
int lower (int c)
{
    return (c >= 'A' && c <= 'Z') ? (c + 'a' - 'A') : c;
}


/*if (c >= 'A' && c <= 'Z')
    {
        return c + 'a' - 'A'; // 65 + 97 - 65 > 97 > 'a'
    }
    else
    {
        return c;
    }*/