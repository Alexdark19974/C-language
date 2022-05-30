#ifndef SYSCALLS_H_
#define SYSCALLS_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h> /* флаги чтения и записи */
#include <malloc.h>
#include <sys/types.h> /* определения типов */
#include <sys/stat.h> /* структура, возвращаемая stat */
#include <dirent.h>

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
#undef fflush
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
	int cnt;		 //сколько осталось символов
	char *ptr;		 //следующая символьная позиция
	char *base;		 //местонахождение буфера
	int flag;		 //режим доступа к файлу
	int fd;			 //дескриптор файлов
} File;

extern File _iob[OPEN_MAX];

#define my_stdin	(&_iob[0])
#define my_stdout	(&_iob[1])
#define my_stderr	(&_iob[2])

enum _flags
{
	_READ	 = 01,		/* файл открыт для чтения */  //b: 00000001
	_WRITE	 = 02,		/* файл открыт для записи */  //b: 00000010
	_UNBUF	 = 04,		/* файл без буферизации */	  //b: 00000100
	_EOF	 = 010,		/* в файле достигнут конец */ //b: 00001000
	_ERR	 = 020,		/* произошла ошибка */ 		  //b: 00010000
};

int _fillbuf(File *);
int _flushbuf(int , File *);
int myfflush(File *);
File *myfopen(char *, char *);
void fsize(char *);
//int mystat(char *, struct mystat *);
void dirwalk(char *, void (*fcn) (char *));

#define feof(p)			(((p)->flag & _EOF) != 0)
#define ferror(p)		(((p)->flag & _ERR) != 0)
#define fileno(p)		((p)->fd)

#define getc(p)		((--(p)->cnt >= 0) ? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define putc(x,p)	(--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x), p))

#define getchar() getc(my_stdin)
#define putchar(x) putc((x), my_stdout)

#endif
