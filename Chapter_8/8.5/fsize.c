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

	static int lock = 0;

	if (!lock)
	{
		printf("    uid\t -  inode   -    mode  -     size\n");
		lock = 1;
	}

	printf("%8d - %8ld - %8d - %8ld %s\n", stbuf.st_uid, stbuf.st_ino, stbuf.st_mode, stbuf.st_size, name);
}
