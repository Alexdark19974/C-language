#include "syscalls.h"

int myfclose(File *fp)
{
	fp->cnt = 0;
	fp->ptr = NULL;

	if (fp->base != NULL)
	{
		free(fp->base);
		fp->base = NULL;
	}

	fp->flags.read = 	0;
	fp->flags.write = 	0;
	fp->flags.unbuf = 	0;
	fp->flags.eof = 	0;
	fp->flags.err = 	0;
	fp->flags.reset = 	0;
	fp->flags.b7 = 		0;
	fp->flags.b8 = 		0;

	if ((close(fp->fd)) == -1)
	{
		return EOF;
	}

	return 0;
}
