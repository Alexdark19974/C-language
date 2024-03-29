#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdarg.h>
#define PERMS 0666 /* Чтение/запись для владельца, группы и остальных */
#define APERMS 0777 /*Absolute freedom*/

void error(char *, ...);

/* cp: копирование файла f1 в f2 */
int main(int argc, char *argv[])
{
	int f1 = 0;
	int f2 = 0;
	int n = 0;
	char buf[BUFSIZ] = {0};

	if (argc != 3)
	{
		error("Usage: cp from to");
	}
	if ((f1 = open(argv[1], O_RDONLY, 0)) == -1)
	{
		error("cp: can't open %s", argv[1]);
	}
	if ((f2 = creat(argv[2], PERMS)) == -1)
	{
		error("cp: can't create %s, mode %03o", argv[2], PERMS);
	}

	while((n = read(f1, buf, BUFSIZ)) > 0)
	{
		if (write(f2, buf, n) != n)
		{
			error("cp: write error on file %s", argv[2]);
		}
	}

	return 0;
}

/* вывод сообщения об ошибке и останов программы */
void error(char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	fprintf(stderr, "error: ");
	vfprintf(stderr, fmt, args);
	fprintf(stderr, "\n");
	va_end(args);
	exit(1);
}

