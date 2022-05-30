#include "syscalls.h"

int myfflush(File fp)
{
	int bufsize = fp->flag & _UNBUF) ? 1 : 5;

	if (fp->cnt > 0)
	{
		write(fp->fd, fp->ptr, bufsize);
		fp->cnt = 0;
	}

	return 0;
}
