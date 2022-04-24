#include <stdio.h>
#include <ctype.h>
#define LIMIT 20

int main(void)
{
	char c = 0;
	char counter = 0;

	while ((c = getchar()) != EOF)
	{
		if (counter == LIMIT)
		{
			puts("");
			counter = 0;
		}
		if (iscntrl(c) || isspace(c))
		{
			printf(" 0x%x ", c);
		}
		else
		{
			putchar(c);
		}

		counter++;
	}

	return 0;
}
