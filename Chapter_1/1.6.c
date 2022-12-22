#include <stdio.h> 
main(void)
{
  int c;

  while (c = (getchar() != EOF))
    printf("%d\n", c);
  printf("%d\n", c);
}
