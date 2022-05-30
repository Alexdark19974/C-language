#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#define STDOUT 1
#define ERROR -1
#define MIN 4

int get(int, long, char *, int);

int main(int argc, char *argv[])
{
	if (argc < MIN)
	{
		fprintf(stderr, "error: minimum is 4 params.\n");
		exit(EXIT_FAILURE);
	}

	int fd = open(argv[1], O_RDONLY, 0);
	char buf[BUFSIZ] = {0};
	int pos = atoi(argv[2]);
	long n = atoi(argv[3]);

	int res = get(fd, pos, buf, n);

	if (res == ERROR)
	{
		fprintf(stderr, "error: sth wrong with get func.\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		write(STDOUT, buf, n);
	}

	exit(EXIT_SUCCESS);
}

/* get: считывание n байт из позиции pos */
int get(int fd, long pos, char *buf, int n)
{
	if (lseek(fd, pos, SEEK_SET) >= 0) /* подход к pos */
	{
		return read(fd, buf, n);
	}
	else
	{
		return ERROR;
	}
}
