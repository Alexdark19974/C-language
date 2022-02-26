#include <stdio.h>
#include <string.h>
#define MAX 100
/*
Adapt the ideas of printd to write a recursive version of itoa ; that is, convert an integer into a string by calling a recursive routine.
*/
/*
Write a recursive version of the function reverse(s) , which reverses the string s in place.
*/
void itoa(int, char[]);
void reverse(char[]);

int main(void)
{
    int n = 12345;
    char array[MAX];

    itoa(n, array);
    printf("%s\n", array);

    reverse(array);
    printf("%s\n", array);

    return 0;
}

void itoa (int n, char array[])
{
    static int i = 0;
    static int sign = 0;
    if ((sign = n) < 0)
    {
        n = -n + 1;
        n = -n;
        printf("%d\n", n);
    }
    if (n / 10) // 123 / 10 > 12 / 10 > 1 / 10 > 0 - NO
    {
        itoa(n / 10, array); // itoa(12, array) >> itoa (1, array)
    }
    array[i++] = (n % 10 + '0');

    if (sign < 0)
    {
        array[i++] = '-';
    }
    array[i] = '\0';
}
void reverse (char array[])
{
    int temp = 0;
    static int i = 0;
    static int counter = 0;
    int j = strlen(array) - 1;

    if (counter < j / 2)
    {
        counter++;
        reverse(array);
    }
    temp = array[i];
    array[i] = array[j - i];
    array[j - i] = temp;
    i++;
}

/*
void reverse (char array[])
{
    void reverser(char[], int);
    
    reverser(array, strlen(array) - 1);
}


void reverser(char array[], int length)
{
    int temp = 0;
    static int i = 0;
    static int counter = 0;
    int j = length;

    if (counter < j / 2)
    {
        counter++;
        reverser(array, j);
    }
    temp = array[i];
    array[i] = array[j - i];
    array[j - i] = temp;
    i++;
}*/