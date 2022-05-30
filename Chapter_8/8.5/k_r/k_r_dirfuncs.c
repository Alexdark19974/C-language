#include "syscalls.h"
#include "dirent.h"
#include "dir.h"
#define DIRSIZ 14

/* opendir: открывает каталог для вызовов readdir */

Dir *myopendir(char *dirname)
{
  int fd = 0;
    struct stat stbuf;
    Dir *dp;

    if ((fd = open(dirname, O_RDONLY, 0)) == -1 || fstat(fd, &stbuf) == -1 || (stbuf.st_mode & S_IFMT) != S_IFDIR || (dp = (Dir *) malloc(sizeof(Dir))) == NULL)
    {
        return NULL;
    }

    dp->fd = fd;


    return dp;
}

/* closedir: закрытие каталога, открытого opendir */
void myclosedir(Dir *dp)
{
	if (dp)
    {
        close(dp->fd);
        free(dp);
    }
}

/* readdir: чтение записей в каталоге по порядку */
Dirent *myreaddir(Dir *dp)
{
    struct direct dirbuf; /* местная структура каталога */
    static Dirent d; /* переносимая структура */

	int n = 0;


	while ((n = read(dp->fd, (char *) &dirbuf, sizeof(dirbuf))) == sizeof(dirbuf))
	{
    	if (dirbuf.d_ino == 0)      /* ячейка не занята */
	    {
	        continue;
	    }

	    d.ino = dirbuf.d_ino;
        strncpy(d.name, dirbuf.d_name, DIRSIZ);
        d.name[DIRSIZ] = '\0'; /* гарантированный конец */
        return &d;
	}

    return NULL;
}

#define MAX_PATH 1024

/* dirwalk: применение fcn ко всем файлам каталога dir */
void dirwalk(char *dir, void (*fcn)(char *))
{
    char name[MAX_PATH];
    Dirent *dp;
    Dir *dfd;

    if ((dfd = myopendir(dir)) == NULL)
    {
        fprintf(stderr, "dirwalk: can't open %s\n", dir);
        return;
    }

    while ((dp = myreaddir(dfd)) != NULL)
    {
        if (strcmp(dp->name, ".") == 0 || strcmp(dp->name, "..") == 0)
        {
            continue; /* пропустить себя и родительский */
        }

        if (strlen(dir) + strlen(dp->name + 2) > sizeof(name))
        {
            fprintf(stderr, "dirwalk: name %s %s too long\n", dir, dp->name);
        }
        else
        {
            sprintf(name, "%s/%s", dir, dp->name);
            (*fcn)(name);
        }
    }
    myclosedir(dfd);
}
