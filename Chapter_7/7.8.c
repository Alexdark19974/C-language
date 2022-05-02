#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <malloc.h>
#define MAXLINE 1000
#define BUF_SIZE 100
#define OVER -1

int get_line(char *, int);

int file_print(int *, ...);

/* find: вывод строк, содержащих образец из последнего аргумента */
/* example input: ./7.7 (-n) include file1.c file2.c */

int main(int argc, char *argv[])
{
	int res = 0;

	if (--argc >= 1)
	{
		argv++;
		res = file_print(&argc, argv, argv + 1, argv + 2);

		if (res)
		{
			printf("paging complete\n");
		}
		else
		{
			fprintf(stderr, "paging failed. No input.\n");
			exit(EXIT_FAILURE);
		}
	}
	return 0;
}


int file_print(int *argc, ...)
{
	char status = 0;
	char **ptr = NULL;
	char **temp_ptr = NULL;
	char i = 0;
	int lineno = 0;
	int page = 0;
	FILE *fp = fopen("result.txt", "w");

	va_list ap;

	va_start(ap, *argc);

	while ((--(*argc) >= 0) && (ptr = va_arg(ap, char **)) != NULL)
	{
		for (temp_ptr = ptr; (*(*temp_ptr + i)) != '\0'; i++)
		{
			if (*(*temp_ptr + i) == '.' && *(*temp_ptr + i + 1) == 'c')
			{
				FILE *ifp = fopen(*temp_ptr, "r");

				page++;
                fprintf(fp,"  %s\t\t\tpage:%d\n", *temp_ptr, page);

				while (status != OVER)
				{
					char c = 0;
					unsigned int j = 0;
					char *c_arr = malloc(BUF_SIZE);

					for (; (c = getc(ifp)) != EOF && (c != '\n'); j++)
					{
						c_arr[j] = c;
					}

					if (c == '\n')
					{
						c_arr[j] = c;
						j++;
						lineno++;
					}

					if (c == EOF)
					{
						c_arr[j] = '\n';
						j++;
						c_arr[j] = '\0';
						status = OVER;
						lineno++;
					}

					c_arr[j] = '\0';

					fprintf(fp,"%d:", lineno);
					fputs(c_arr, fp);
					free(c_arr);
				}

				status = 0;
				fclose(ifp);
			}
		}
		i = 0;
	}

	va_end(ap);
	fclose(fp);
	return page;
}
