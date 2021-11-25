#include <stdio.h>
#define sizemax 5

void array_reverse(int* , int );

void array_reverse_ptr(int*, int*);

int main(void) 
{
  int array[sizemax] = {0};

  for (int i = 0; i < sizemax; i++)
  {
      scanf ("%d", &array[i]);
  }
  
  array_reverse(array, sizemax);
  
  for (int i = 0; i < sizemax; i++)
  {
    printf("%d ", array[i]);
  }
  puts("");

  array_reverse_ptr(array, array + sizemax);

  for (int i = 0; i < sizemax; i++)
  {
    printf("%d ", array[i]);
  }
    return 0;
}

void array_reverse(int* array, int size) 
{
  for (int i = 0; i < size/2; i++)
  {
    int temp = array[i];
    array[i] = array[size - i - 1];
    array[size - i - 1] = temp;
  }
}
void array_reverse_ptr(int* array, int* limit) 
{
    for (int *i = array; i < limit; i++, limit--)
    {
        int tmp = *i;
        *i = *(limit - 1);
        *(limit - 1) = tmp;
    }
}