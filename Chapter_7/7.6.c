#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#define OVER -1
#define BUF_SIZE 100

int cmp_print(char *, char *);

int main(int argc, char *argv[])
{
	int res = 0;

	if (argc > 2)
	{
		res = cmp_print(argv[1], argv[2]);
	}
	else
	{
		fprintf(stderr, "Nothing to compare\n");
		exit(EXIT_FAILURE);
	}

	if (!res)
	{
		printf("Files are indentical\n");
	}
	else
	{
		printf("The difference has been found\n");
	}

	return 0;
}

int cmp_print(char *arg1, char *arg2)
{
	FILE *fp_1 = fopen(arg1, "r");

	if (fp_1 == NULL)
	{
		fprintf(stderr,"%s: such file doesn't exist.\n", arg1);
		exit(EXIT_FAILURE);
	}

	FILE *fp_2 = fopen(arg2, "r");

	if (fp_2 == NULL)
	{
		fprintf(stderr,"%s: such file doesn't exist.\n", arg2);
		exit(EXIT_FAILURE);
	}

	FILE *fp_3 = fopen("result.txt", "w");

	int status = 0;
	char line = 0;
	char *c_1_arr = NULL;
	char *c_2_arr = NULL;

	while (status != OVER)
	{
		char c = 0;
		int i = 0;
		int j = 0;
		c_1_arr = malloc(BUF_SIZE);
        c_2_arr = malloc(BUF_SIZE);

		for (; (c = getc(fp_1)) != EOF && (c != '\n'); i++)
		{
			c_1_arr[i] = c;
		}

		if (c == '\n')
		{
			c_1_arr[i] = c;
			i++;
		}
		if (c == EOF)
        {
			line++;
        	status = OVER;
        }

		c_1_arr[i] = '\0';

		for (; (c = getc(fp_2)) != EOF && (c != '\n'); j++)
		{
       		c_2_arr[j] = c;
		}

		if (c == '\n')
        {
			line++;
			c_2_arr[j] = c;
			j++;
        }
	    if (c == EOF)
        {
			status = OVER;
        }
		c_2_arr[j] = '\0';

		if (strcmp(c_1_arr, c_2_arr) != 0)
		{
			fprintf(fp_3,"\tLine that differ is %d\n", line);
			fputs(c_1_arr, fp_3);
			fputs(c_2_arr, fp_3);
			fclose(fp_1);
			fclose(fp_2);
			fclose(fp_3);
			return 2;
		}

		free(c_1_arr);
		free(c_2_arr);
		i = 0;
		j = 0;
	}

	fclose(fp_1);
	fclose(fp_2);
	fclose(fp_3);

	return EOF;
}
