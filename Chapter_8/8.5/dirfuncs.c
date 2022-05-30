#include "syscalls.h"
#include "dirent.h"
#include "dir.h"
#define DIRSIZ 14

/* opendir: открывает каталог для вызовов readdir */

DIR *myopendir(char *dirname)
{
	DIR *dp = opendir(dirname);

	if (dp == NULL)
	{
		fprintf(stderr, "can't open directory\n");
		return NULL;
	}

	return dp;
}

/* closedir: закрытие каталога, открытого opendir */
void myclosedir(DIR *dp)
{
	closedir(dp);
}

/* readdir: чтение записей в каталоге по порядку */
struct dirent *myreaddir(DIR *dp)
{
	static struct dirent *d;

	while ((d = readdir(dp)) != NULL)
	{
		return d;
	}

	return NULL;
}
