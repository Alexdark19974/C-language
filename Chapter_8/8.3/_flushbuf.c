
#include "syscalls.h"

/* очистка заполненного буфера */

int _flushbuf(int c, File *fp)
{
//	printf("fd of stdin is %d\n", fileno(fp));

	int bufsize = 0;
	int static flag = 0;
	char c_c = (char) c;

	if ((fp->flag & (_WRITE | _EOF | _ERR)) != _WRITE)
	{
		return EOF;
	}

	bufsize = (fp->flag & _UNBUF) ? 1 : 5;

	if (fp->base == NULL)
	{
		if ((fp->base = (char *) malloc(bufsize)) == NULL)
		{
			return EOF;
		}
	}

	fp->ptr = fp->base;

	if (fp->flag & _UNBUF)
	{
		write(fp->fd, &c, 4);
		fp->cnt = 0;
	}
	else
	{
		if (fp->cnt == -1 && !flag)
		{
			write(fp->fd, &c_c, 1);
			fp->cnt = bufsize;
			flag = ON;
		}
		else if (fp->cnt == -1 && flag)
		{
			write(fp->fd, fp->ptr, bufsize);
			write(fp->fd, &c_c, 1);
			fp->ptr = fp->base;
			flag = OFF;
			fp->cnt = 0;
		}
	}

	return 0;
}
