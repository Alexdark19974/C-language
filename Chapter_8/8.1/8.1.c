#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <stdarg.h>
#define STDOUT 1
#define STDIN 0

void error(char *, ...);

int main (int argc, char *argv[])
{
    void filecopy(int , int);
    char *prog = argv[0];
	int fd = 0;

    if (argc == 1)
    {
        filecopy(STDIN, STDOUT);
    }
    else
    {
        while (--argc > 0)
        {
            if ((fd = open(*++argv, O_RDONLY, 0)) == -1)
            {
                fprintf(stderr,"%s: can't open %s\n", prog, *argv);
                exit(EXIT_FAILURE);
            }
            else
            {
                filecopy(fd, STDOUT);
                close(fd);
            }
        }
    }

	long int time = clock();

	printf("Time taken is %ld\n", time);

    exit(EXIT_SUCCESS);
}

void filecopy(int fd1, int fd2)
{
	char buf[BUFSIZ] = {0};
	int n = 0;
	int check = 0;
    while ((n = read(fd1, buf, BUFSIZ)) > 0)
    {
        check = write(fd2, buf, n);

		if (check != n)
		{
			error("low_cat: write error on file with file descriptor %d", fd2);
			exit(EXIT_FAILURE);
		}
    }
}

void error(char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	fprintf(stderr, "error: ");
	vfprintf(stderr, fmt, args);
	fprintf(stderr, "\n");
	va_end(args);
	exit(EXIT_FAILURE);
}
