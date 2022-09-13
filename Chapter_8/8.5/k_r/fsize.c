#include "syscalls.h"
#include "dirent.h"

/* вывод размеров файлов */
int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		fsize(".");
	}
	else
	{
		while (--argc > 0)
		{
			fsize(*(++argv));
		}
	}

	return 0;
}

void fsize(char *name)
{
	struct stat stbuf;

	if (stat(name, &stbuf) == -1)
	{
		fprintf(stderr, "fsize: can't access %s\n", name);
		return;
	}
	if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
	{
		dirwalk(name, fsize);
	}

	printf("%81ld %s\n", stbuf.st_size, name);
}
