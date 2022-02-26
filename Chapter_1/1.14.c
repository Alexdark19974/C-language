#include <stdio.h>
#define MAXSIZE 255

void symbol_display_horizontal (int array[])
{
    puts("\nHorizontal symbol count\n");
    puts("-----------------------\n");
    for (int i = 0; i < MAXSIZE; i++)
    {
        if (array[i] > 0)
        {
            if (i < 100)
            {
                printf(" %d: ", i + 1);
            }
            else
            {
                printf("%d: ", i + 1);
            }

            for (int j = 0; j < array[i]; j++)
            {
               printf("# ");
            }
            puts("");
        }
        else
        {
            continue;
        }
    }
}

void symbol_display_vertical (int array[], int max_length_count)
{
    puts("\nVertical symbol count\n");
    puts("-----------------------\n");

    for (int i = 0; i < max_length_count; i++)
    {
        for (int j = 0; j < MAXSIZE; j++)
        {
          if (array[j] < 1)
          {
            continue;
          }

            if (array[j] >= max_length_count - i)
            {
                printf(" #   ");
            }
            else 
            {
               printf("     ");
            }
        }
        puts("\n");
    }

   for (int i = 0; i < MAXSIZE; i++)
    {
        if (array[i] > 0 && i < 100)
        {
            printf(" %d  ", i + 1);
        }
        else if (array[i] > 0 && i > 100)
        {
          printf(" %d ", i + 1);
        }
    }
}

int main(void) 
  { 
    char c; 
    int array[MAXSIZE] = {0}; 
    int max_length_count = 0; 
    int counter = 0; 

    while((c = getchar()) != EOF && c < MAXSIZE) 
    {
        if (c >= 0 && c <= 255)
        {
            array[c]++;
        } 
    }
    for (int i = 0; i < MAXSIZE; i++)
    {
        if (max_length_count < array[i] && array[i] > 0)
        {
            max_length_count = array[i];
        }
    }
    symbol_display_horizontal(array);
    symbol_display_vertical (array, max_length_count);
    
    return 0;
}