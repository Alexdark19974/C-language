#include "syscalls.h"

/* _fillbuf: создание и заполненмие буфера ввода */

int _fillbuf(File *fp)
{
	//printf("fd of stdout is %d\n", fileno(fp));
	int bufsize = 0;

	if ((fp->flags.read != 1))
	{
		return EOF;
	}

	bufsize = (fp->flags.unbuf == 1) ? 1 : BUFSIZ;

	if (fp->base == NULL) /* буфера ещё нет */
	{
		if ((fp->base = (char *) malloc(bufsize)) == NULL)
		{
			return EOF;			/* не удаётся создать буфер */
		}
	}
	fp->ptr = fp->base;			/* указатель на начало буфера */
	fp->cnt = read(fp->fd, fp->ptr, bufsize);
	//fp->cnt = -2;

	if (--fp->cnt < 0)
	{
		if (fp->cnt == -1)
		{
			fp->flags.eof = 1;
			printf("Status of EOF is %d\n",feof(fp));
		}
		else
		{
			fp->flags.err = 1;
			fprintf(stderr, "Status of error is %d\n", ferror(fp));
		}

		fp->cnt = 0;

		return EOF;
	}

	return (unsigned char) *fp->ptr++;
}
