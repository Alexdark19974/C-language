#include "syscalls.h"

/* очистка заполненного буфера */

int _flushbuf(int c, File *fp)
{
//	printf("fd of stdin is %d\n", fileno(fp));

	int bufsize = 0;
//	int static flag = 0;
	char c_c = (char) c;

	if ((fp->flags.write != ON))
	{
		return EOF;
	}

	bufsize = (fp->flags.unbuf == ON) ? 1 : BUFSIZ;

	if (fp->base == NULL)
	{
		if ((fp->base = (char *) calloc(bufsize, 1)) == NULL)
		{
			return EOF;
		}
	}

	fp->ptr = fp->base;

	if (fp->flags.unbuf == ON)
	{
		write(fp->fd, &c_c, ON);
		fp->cnt = 0;
	}
	else
	{
		if (fp->cnt == -1 && fp->flags.reset == OFF)
		{
			write(fp->fd, &c_c, 1);
			fp->cnt = bufsize;
			fp->flags.reset = ON;
		}
		else if (fp->cnt == -1 && fp->flags.reset == ON)
		{
			write(fp->fd, fp->ptr, bufsize);
			write(fp->fd, &c_c, 1);
			fp->ptr = fp->base;
			fp->flags.reset = OFF;
			fp->cnt = 0;
		}
	}

	return 0;
}
