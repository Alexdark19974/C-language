#ifndef SYSCALLS_H_
#define SYSCALLS_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <malloc.h>

#undef getc
#undef getchar
#undef putc
#undef putchar
#undef feof
#undef ferror
#undef fileno
#undef stdin
#undef stdout
#undef stderr
#undef fopen
#undef BUFSIZ
#undef NULL

#define NULL 		0
#define EOF 		(-1)
#define BUFSIZ 		1024
#define OPEN_MAX	 20 /* максимальное количество открытых файлов */
#define ON 1
#define OFF 0

typedef struct _iobuf
{
    int cnt;        /* сколько осталось символов */
    char *ptr;      /* следующая символьная позиция */
    char *base;     /* местонахождение буфера */
    struct
	{
		unsigned char read 	: 	1;
		unsigned char write : 	1;
		unsigned char bit6 	: 	1;
		unsigned char unbuf : 	1;
		unsigned char eof 	:   1;
		unsigned char err 	:   1;
		unsigned char b7 	: 	1;
		unsigned char b8 	: 	1;

	} flags;       		/* режим доступа к файлу */
    int fd;         /* дескриптор файлов */

} File;

extern File _iob[OPEN_MAX];

#define my_stdin	(&_iob[0])
#define my_stdout	(&_iob[1])
#define my_stderr	(&_iob[2])

int _fillbuf(File *);
int _flushbuf(int , File *);
File *myfopen(char *, char *);

#define feof(p)			(((p)->flags.eof == 1) ? 1 : 0)
#define ferror(p)		(((p)->flags.err == 1) ? 1 : 0)
#define fileno(p)		((p)->fd)

#define getc(p)		((--(p)->cnt >= 0) ? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define putc(x,p)	(--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x), p))

#define getchar() getc(my_stdin)
#define putchar(x) putc((x), my_stdout)

#endif
