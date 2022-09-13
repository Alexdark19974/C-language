#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdarg.h>
#include <ctype.h>

int minscanf(char *, ...);

int main (void)
{
	int d = 0;
	char c = 0;
	int res = 0;
	char *string = calloc(100, sizeof(char));
	float f = 0.0;

	/*
		Primitive function scanf: minscanf;
		takes an undefined number of arguments and returns the number of succesfully processed arguments
		or EOF if an error occurs
	*/
	res = minscanf("%d %f %c %s ", &d, &f, &c, string);

	if (res == EOF)
	{
		exit(EXIT_FALIURE);
	}

	printf("Result is: %d and %f and %c and %s;\nArgnumber is %d;\n", d, f, c, string, res);

	free(string);

	return 0;
}

int minscanf(char *format, ...)
{
	va_list ap;
	char *ptr = NULL;
	int *ival = NULL;
	char *cval = NULL;
	char *sval = NULL;
	float *fval = NULL;
	int counter = 0;

	va_start(ap, format);

	for (ptr = format; *ptr; ptr++)
	{
		if (isspace(*ptr))
        {
			if ((*(ptr + 1)) == '\0') // if there is a non-printable character such as '\n' or ' ' at the end of the format string
			{                         // the program emulates the works of scanf, that is, it will consume any non-printable character
				char tmp = 0;		  // until a printable-charachter is met

				while (isspace(tmp = getchar()))
				{
					;
				}
			}
            continue;
        }
		if (*ptr == '%')
		{
			ptr++;
		}
		switch(*ptr)
		{
			case 'd':
			{
				ival = va_arg(ap, int *);
				scanf(" %d", ival);
				counter++;
				break;
			}
			case 'c':
			{
				cval = va_arg(ap, char *);
				scanf(" %c", cval);
				counter++;
				break;
			}
			case 's':
			{
				sval = va_arg(ap, char *);
				scanf(" %s", sval);
				counter++;
				break;
			}
			case 'f':
			{
				fval = va_arg(ap, float *);
				scanf(" %f", fval);
				counter++;
				break;
			}
			default:
			{
				printf("error: unknown specifier");
				va_end(ap);
				return EOF:
			}
		}
	}
	va_end(ap);
	return counter;
}
