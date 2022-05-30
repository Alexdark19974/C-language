#include "syscalls.h"

#define PERMS 0666 /* разрешены чтение и запись */
			 /* для владельца, группы и остальных  */

/* fopen: открытие файла с возвращением файлового указателя  */

File *myfopen(char *name, char *mode)
{
	int fd;
	File *fp;

	if (*mode != 'r' && *mode != 'w' && *mode != 'a')
	{
		return NULL;
	}

	for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
	{
		/*if ((fp->flag & (_READ | _WRITE)) == 0)
		{
			break;		  найдено свободное место для файла
		}*/
		if ((fp->flags.write == OFF && fp->flags.read == OFF))
		{
			break;
		}
	}

	if (fp >= _iob + OPEN_MAX) /* нет свободных места для файла */
	{
		return NULL;
	}

	if (*mode == 'w')
	{
		fd = creat(name, PERMS);
	}
	else if (*mode == 'a')
	{
		if ((fd = open(name, O_WRONLY, 0)) == -1)
		{
			fd = creat(name, PERMS);
		}
		lseek(fd, 0L, SEEK_END);
	}
	else
	{
		fd = open(name, O_RDONLY, 0);
	}

	if (fd == -1)		/* указанное имя недоступно */
	{
		return NULL;
	}

	fp->fd = fd;
	fp->cnt = 0;
	fp->base = NULL;
//	fp->flag = (*mode == 'r') ? _READ: _WRITE;

	if (*mode == 'r')
	{
		fp->flags.read = ON;
	}
	else
	{
		fp->flags.write = ON;
	}
	return fp;
}
