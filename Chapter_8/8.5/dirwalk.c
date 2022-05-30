#include "syscalls.h"
#include "dirent.h"

#define MAX_PATH 1024

/* dirwalk: применение fcn ко всем файлам каталога dir */
void dirwalk(char *dir, void (*fcn)(char *))
{
	char name[MAX_PATH];
	struct dirent *dp;
	DIR *dfd = NULL;


	if ((dfd = myopendir(dir)) == NULL)
	{
		fprintf(stderr, "dirwalk: can't open %s\n", dir);
		return;
	}

	while ((dp = myreaddir(dfd)) != NULL)
	{
		if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
		{
			continue; /* пропустить себя и родительский */
		}

		if (strlen(dir) + strlen(dp->d_name + 2) > sizeof(name))
		{
			fprintf(stderr, "dirwalk: name %s %s too long\n", dir, dp->d_name);
		}
		else
		{
			sprintf(name, "%s/%s", dir, dp->d_name);
			(*fcn)(name);
		}
	}
	myclosedir(dfd);
}
