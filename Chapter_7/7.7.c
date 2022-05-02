#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#define MAXLINE 1000
#define BUF_SIZE 100
#define OVER -1
#define FOUND 2
#define NOT_FOUND 1

int get_line(char *, int);

int grep(char **, char **, char **, int, int);

/* find: вывод строк, содержащих образец из последнего аргумента */
/* example input: ./7.7 (-n) include file1.c file2.c */

int main(int argc, char *argv[])
{
	char line[MAXLINE] = {0};
	long int lineno = 0;
	int c = 0;
	int except = 0;
	int number = 0;
	int found = 0;
	int eof_check = 0;
	int res = 0;

	while (--argc > 0 && (*++argv)[0] == '-')
	{
		while ((c = *++argv[0]))
		{
			switch (c)
			{
				case 'x':
				{
					except = 1;
					break;
				}
				case 'n':
				{
					number = 1;
					break;
				}
				default:
				{
					printf("find: illegal option %c\n", c);
					argc = 0;
					found = -1;
					break;
				}
			}
		}
	}

	if (argc >= 2)
	{
		res = grep(argv, (argv + 1), (argv + 2), number, except);

		if (res == FOUND)
		{
			printf("pattern found\n");
		}
		else
		{
			printf("patern not found\n");
			exit(1);
		}
	}
	else if (argc < 1)
	{
		printf("Usage: find -x -n pattern\n");
	}
	else
	{
		while ((eof_check = get_line(line, MAXLINE)) > 0 && eof_check != EOF)
		{
			lineno++;
			if ((strstr(line, *argv) != NULL) != except)
			{
				if (number)
				{
					printf("%ld:", lineno);
				}
				printf ("%s", line);
				found++;
			}
		}
	}

	return found;
}

int get_line(char *s, int max)
{
	char c = 0;
	unsigned char i = 0;

    for (; (i < --max) && ((c = getchar()) != EOF) && (c != '\n'); i++)
    {
        s[i] = c;
    }

    if (c == '\n')
    {
        s[i] = c;
		i++;
		s[i] = '\0';
    }

    if (c == EOF)
    {
        s[i] = '\0';
		return EOF;
    }

	return i;
}

int grep (char **arg1, char **arg2, char **arg3, int number, int except)
{
	char status = 0;
	char line_1 = 0;
	char line_2 = 0;
	char match_counter = 0;

	FILE *fp_1 = fopen(*arg2, "r");

	if (fp_1 == NULL)
    {
        fprintf(stderr,"%s: such file doesn't exist.\n", *arg2);
    }

    FILE *fp_2 = fopen(*arg3, "r");

    if (fp_2 == NULL)
    {
        fprintf(stderr,"%s: such file doesn't exist.\n", *arg3);
    }

	FILE *fp_3 = fopen("result.txt", "w");

	while (status != OVER)
	{
		char c = 0;
        int i = 0;
        int j = 0;
        char *c_1_arr = malloc(BUF_SIZE);
        char *c_2_arr = malloc(BUF_SIZE);

		if (fp_1)
		{
			for (; (c = getc(fp_1)) != EOF && (c != '\n'); i++)
        	{
            	c_1_arr[i] = c;
        	}

        	if (c == '\n')
        	{
            	c_1_arr[i] = c;
            	i++;
				line_1++;
        	}

        	if (c == EOF)
        	{
           		line_1++;
            	status = OVER;
        	}

        	c_1_arr[i] = '\0';
		}

		if (fp_2)
		{
        	for (; (c = getc(fp_2)) != EOF && (c != '\n'); j++)
        	{
            	c_2_arr[j] = c;
        	}

        	if (c == '\n')
        	{
            	line_2++;
            	c_2_arr[j] = c;
            	j++;
        	}

        	if (c == EOF)
        	{
            	status = OVER;
				line_2++;
        	}

        	c_2_arr[j] = '\0';
		}

		if (except)
		{
			if (fp_1)
			{
				if (strstr(c_1_arr, *arg1) == NULL)
        		{
           			if (number)
            		{
                		fprintf(fp_3,"%s:%d:", *arg2, line_1);
                		fputs(c_1_arr, fp_3);
            		}
            		else
            		{
                		fprintf(fp_3, "%s:", *arg2);
                		fputs(c_1_arr, fp_3);
            		}

					match_counter++;
        		}
			}

			if (fp_2)
			{
        		if (strstr(c_2_arr, *arg1) == NULL)
        		{
            		if (number)
            		{
                		fprintf(fp_3, "%s:%d:", *arg3, line_2);
                		fputs(c_2_arr, fp_3);
            		}
            		else
            		{
                		fprintf(fp_3, "%s:", *arg3);
                		fputs(c_2_arr, fp_3);
            		}

					match_counter++;
        		}

				free(c_1_arr);
	        	free(c_2_arr);
				continue;
			}
		}

		if (fp_1)
		{
			if (strstr(c_1_arr, *arg1))
			{
				if (number)
				{
					fprintf(fp_3,"%s:%d:", *arg2, line_1);
                	fputs(c_1_arr, fp_3);
				}
				else
				{
					fprintf(fp_3, "%s:", *arg2);
					fputs(c_1_arr, fp_3);
				}

				match_counter++;
			}
		}

		if (fp_2)
		{

			if (strstr(c_2_arr, *arg1))
			{
				if (number)
				{
					fprintf(fp_3, "%s:%d:", *arg3, line_2);
                	fputs(c_2_arr, fp_3);
				}
				else
				{
					fprintf(fp_3, "%s:", *arg3);
					fputs(c_2_arr, fp_3);
				}

				match_counter++;
			}

			free(c_1_arr);
   			free(c_2_arr);
		}
	}

	if (fp_1)
	{
		fclose(fp_1);
	}

	if (fp_2)
	{
		fclose(fp_2);
	}

	fclose(fp_3);

	return (match_counter > 0) ? FOUND : NOT_FOUND;
}
