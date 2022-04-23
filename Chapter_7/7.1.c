#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[])
{

// the examination start from the end of the name of the program.
// if the last letter is an upper case, the the program will convert everything to upper-case values: uppeR -> lower to upper, uPper -> upper to lower
// if the last letter is an lower case, the program will convert everything to lower-case values: LOWEr -> upper to lower

	int c = 0;

	int len = strlen(*argv);

	if (isupper(*(*argv + len - 1)))
	{
		while ((c = getchar()) != EOF)
		{
			putchar(toupper(c));
		}
	}
	else
	{
		while ((c = getchar()) != EOF)
		{
			putchar(tolower(c));
		}
	}

	return 0;
}
