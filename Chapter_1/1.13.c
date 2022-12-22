#include <stdio.h>

/* count digits, white space, others */
main()
{
    int c, i, j, tmp, nwhite, nother, nchar;
    int ndigit[10];
    int nwordlen[100];
    nwhite = nother = nchar = 0;
    for (i = 0; i < 10; ++i)
        ndigit[i] = 0;
    for (i = 0; i < 100; ++i)
        nwordlen[i] = 0;
    i = 0;
    while ((c = getchar()) != EOF)
        if (c >= '0' && c <= '9')
            ++ndigit[c-'0'];
        else if (c == ' ' || c == '\n' || c == '\t') {
            if (nchar) {
                nwordlen[i] = nchar;
                ++i;
                if (i == 99) {
                    printf("warning: the end of an array has been reached.\nAt this point, it will rewrite itself starting at index 0.\n");
                    i = 0;
                }
            }
            ++nwhite;
            nchar = 0;
        }
        else {
            ++nother;
            if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
                ++nchar;
        }
   printf("digits = ");
   for (i = 0; i < 10; ++i)
       printf(" %d", ndigit[i]);
   printf(", white space = %d, other = %d\n",
       nwhite, nother);

   printf("----Horizontal histogram-----\n"); 
   for (i = 0; nwordlen[i] != 0; ++i) {
       printf("word%d: ", i + 1);
       for (c = nwordlen[i]; c > 0; --c)
           printf("#");
       putchar('\n');
   }

   printf("----Vertical histogram----\n");
   for (nother = 0; nwordlen[nother] != 0; ++nother)
       printf("word%d ", nother);
   putchar('\n');

   tmp = nother;
   for (i = 0; tmp > 0; i++) {
       tmp = nother;
       for (j = 0; tmp != 0 && nwordlen[j] != 0; j++) {
           if (nwordlen[j] > i)
               printf("   # ");
           else {
               printf("     ");
               --tmp;
           }
       }
       putchar('\n');
   }
   putchar('\n');
}
