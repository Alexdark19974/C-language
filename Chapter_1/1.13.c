#include <stdio.h>
#define MAXSIZE 10

void HORIZONTAL (int array[])
{
    printf("\nHORIZONTAL\n");
    
    for (int i = 0; i < MAXSIZE; i++)
    {
        printf("%2d:", i);

        for (int j = 0; j < array[i]; j++)
        {
            printf(" # ");
        }
        printf("\n");
    }
}

void VERTICAL (int array[], int max_length)
{
    printf("\nVERTICAL\n");
    for (int i = 0; i < max_length; i++)
    {
        for (int j = 0; j < MAXSIZE; j++)
        {
            if (array[j] >= max_length - i)
            {
                printf("# ");
            }
            else
            {
                printf("  ");
            }
        }
        printf("\n");
    }

    for (int i = 0; i < MAXSIZE; i++)
    {
        printf("%d ", i);
    }
}
int main(void)
{
    int c;
    int array[MAXSIZE] = {0};
    int counter_s = 0;
    int max_length = 0;
    int i = 0;

    while ((c = getchar()) != EOF && i < 10)
    {
        if (c != ' ' && c != '\n' && c != '\t')
        {
            counter_s++;  
            i++;      
        }
        else
        {
            array[i] = counter_s;

            if (array[i] > max_length)
            {
                max_length = array[i];
            }
            i = 0;
            counter_s = 0;
        }
    }

    if (counter_s && i < 10)
    {
        if (max_length < counter_s)
        {
            max_length = counter_s;
        }

        array[i] = counter_s;
    }

    HORIZONTAL(array);
    VERTICAL(array, max_length);
    
    return 0;
}