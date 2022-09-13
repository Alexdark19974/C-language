#include "syscalls.h"

int myfflush(File *fp)
{
	int bufsize = (fp->flags.unbuf == ON) ? 1 : BUFSIZ;

	if (fp->cnt > 0)
	{
		fp->ptr = fp->base;
		write(fp->fd, fp->ptr, bufsize);
		fp->cnt = 0;
		free(fp->base);
		fp->base = NULL;
		fp->ptr = NULL;
		fp->flags.reset = OFF;
	}

	return 0;
}
