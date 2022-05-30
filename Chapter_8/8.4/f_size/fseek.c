#include "syscalls.h"

int myfseek(File *fp, long offset, int origin)
{
	int len = 0;

	if (fp->ptr == NULL)
	{
		lseek(fp->fd, offset, origin);
	}
	else
	{
		switch(origin)
		{
			case SEEK_CUR :
			{
				len = strlen(fp->base);

				if (offset <= 0 && (offset + len) >= 0)
				{
					fp->ptr+= (char) offset;

					if (fp->ptr < fp->base)
					{
						fprintf(stderr, "error: attempt to reach space outside the allocated space.\n");
                    	exit(EXIT_FAILURE);
					}
				}
				else if (offset >= 0 && fp->ptr == fp->base && offset <= BUFSIZ - 1)
				{
					fp->ptr+= (char) offset;
				}
				else if (offset >= 0 && fp->ptr != fp->base && (offset + (len - fp->cnt)) <= BUFSIZ - 1)
				{
					fp->ptr+= (char) offset;
				}
				else
				{
					fprintf(stderr, "error: attempt to reach space outside the allocated space.\n");
                    exit(EXIT_FAILURE);
				}
				break;
			}
			case SEEK_SET :
			{
				fp->ptr = fp->base;

				if (offset >= 0 && (offset <= (BUFSIZ - 1)))
				{
					fp->ptr+= (char) offset;
				}
				else
				{
					fprintf(stderr, "error: attempt to reach space outside the allocated space.\n");
                    exit(EXIT_FAILURE);
				}
				break;
			}
			case SEEK_END :
			{
				len = strlen(fp->base);

				fp->ptr = fp->base;

				fp->ptr+= (char) len;

				if (offset <= 0 && ((offset + len) >= 0))
				{
					fp->ptr+= (char) offset;
				}
				else if (offset >= 0 && (offset + len) <= (BUFSIZ - 1))
				{
					fp->ptr+= (char) len;
				}
				else
				{
					fprintf(stderr, "error: attempt to reach space outside the allocated space.\n");
                    exit(EXIT_FAILURE);
				}
				break;
			}
			default :
			{
					fprintf(stderr, "error: invalid origin.\n");
                    exit(EXIT_FAILURE);
			}
		}
	}

	return 0;
}
