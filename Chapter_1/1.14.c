#include <stdio.h>

/* count digits, white space, others */
main()
{
    int c, i, j, tmp, nwhite, nline, nother, nchar, ntab, nexclam, nquest;
    int ndigit[10];
    int nwordlen[100];
    nwhite = nother = nline = nchar = nexclam = nquest = ntab = 0;
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

            if (c == ' ')
                ++nwhite;
            else if (c == '\t')
                ++ntab;
            else if (c == '\n')
                ++nline;
            nchar = 0;
        }
        else {
            ++nother;
            if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
                ++nchar;
            else if (c == '?')
                ++nquest;
            else if (c == '!')
                ++nexclam;
        }
   printf("digits = ");
   for (i = 0; i < 10; ++i)
       printf(" %d", ndigit[i]);
   printf(", white space = %d, new line = %d, tab = %d, question mark = %d, exclamation mark = %d\n",
       nwhite, nline, ntab, nquest, nexclam);
   printf("         ");
   for (i = 0; i < 10; ++i)
       printf(" %d", i);
   putchar('\n');
   printf("----Horizontal histogram-----\n"); 
   for (i = 0; nwordlen[i] != 0; ++i) {
       printf("word%d: ", i + 1);
       for (c = nwordlen[i]; c > 0; --c)
           printf("#");
       putchar('\n');
   }
   
   i = nexclam;
   printf("!:");
   while (i) {
       printf(" #");
       --i;
   }
   putchar('\n');
   i = nquest;
   printf("?:");
   while (i) {
       printf(" #");
       --i;
   }
   putchar('\n');
   i = nwhite;
   printf("\' \':");
   while (i) {
       printf(" #");
       --i;
   }
   putchar('\n');
   i = ntab;
   printf("\\t:");
   while (i) {
       printf(" #");
       --i;
   }
   putchar('\n');
   i = nline;
   printf("\\n:");
   while (i) {
       printf(" #");
       --i;
   }
   putchar('\n');
   printf("----Vertical histogram----\n");

   printf(" !  ?  \' \' \\t   \\n");
   for (nother = 0; nwordlen[nother] != 0; ++nother)
       printf(" word%d", nother + 1);
   putchar('\n');
   tmp = nother;
   for (i = 0; tmp > 0; i++) {
       tmp = nother;
       if (nexclam > 0) {
           printf(" # ");
           --nexclam;
       } else
           printf("   ");
       if (nquest > 0) {
           printf(" # ");
           --nquest;
       } else
           printf("   ");
       if (nwhite > 0) {
           printf("  # ");
           --nwhite;
       } else
           printf("    ");
       if (ntab > 0) {
           printf("  #   ");
           --ntab;
       } else
           printf("      ");
       if (nline > 0) {
           printf(" #  ");
           --nline;
       } else
           printf("    ");

       for (j = 0; tmp != 0 && nwordlen[j] != 0; j++) {
           if (nwordlen[j] > i)
               printf("  #   "); 
           else {
               printf("      ");
               --tmp;
           }
       }
       putchar('\n');
   }

   for (; nexclam > 0 || nquest > 0 || nwhite > 0 || ntab > 0 || nline > 0 ;) {
       if (nexclam > 0) {
           printf(" ? ");
           --nexclam;
       } else
           printf("   ");
       if (nquest > 0) {
           printf(" ?  ");
           --nquest;
       } else
           printf("    ");
       if (nwhite > 0) {
           printf(" ? ");
           --nwhite;
       } else
           printf("   ");
       if (ntab > 0) {
           printf("  ?");
           --ntab;
       } else
           printf("   ");
       if (nline > 0) {
           printf("    ? ");
           --nline;
       } else
           printf("    ");
       putchar('\n');
   }
   putchar('\n');
}
