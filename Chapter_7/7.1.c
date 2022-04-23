#include <stdio.h>
#include <ctype.h>

main()
{
	while ((c = getchar()) != EOF)
	putchar(tolower(c));
	return 0;
}
