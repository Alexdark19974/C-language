#ifndef _SYSCALLS_H_
#define _SYSCALLS_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>
#include <errno.h>
#include <ctype.h>
#if defined (LSEEK_CASE)
#define DEFAULT_SIZE    BUFSIZ
#define DEFAULT_POS     0
#define DEFAULT_OFFSET  0
typedef struct params {
    int offset;
    int size;
    long pos;
} params, *paramsP;
int read_and_print_file_at_pos(char **, params);
int get(int , char *, params);
#endif
#if defined(FFUNC_CASE)
#undef NULL
#undef EOF
#undef BUFSIZ
#undef FILE
#define NULL        0
#define EOF         (-1)
#define BUFSIZ      1024 // for proper null-termination
#define OPEN_MAX    20 /*max #files open at once */
#define PERMS       0666
#define FLUSHED     0
#define OK          0
#define ERR      -1
typedef struct _iobuf {
    int  cnt;       /* characters left */
    char *ptr;      /* next character position */
    char *base;     /* location of buffer */
    struct {
        uint READ:  1;
        uint WRITE: 1;
        uint UNBUF: 1;
        uint _EOF:  1;
        uint _ERR:  1;
    };
    int flag;       /* mode of file access */
    int fd;         /* file descriptor */

} _FILE;

extern _FILE _iob[OPEN_MAX];
#undef stdin
#undef stdout
#undef stderr
#define stdin   (&_iob[0])
#define stdout  (&_iob[1])
#define stderr  (&_iob[2])

enum _flags {
    _READ   = 01,       /* file open for reading */
    _WRITE  = 02,       /* file open for writing */
    _UNBUF  = 04,       /* file is unbuffered */
    _EOF    = 010,      /* EOF has occurred on this file */
    _ERR    = 020       /* error ocurred on this file */
};

_FILE *_fopen(char *, char *);
int _fillbuf(_FILE *);
int _fprintf(_FILE *, char *, ...);
void _flushbuf(int, _FILE *);
void __exit(void);
int copy(char **);

#define _feof(p)         (((p)->flag & _EOF) != 0)
#define _ferror(p)       (((p)->flag & _ERR) != 0)
#define _fileno(p)       ((p)->fd)

#undef  getc
#define getc(p)     (--(p)->cnt >= 0 \
                ?   (unsigned char) *(p)->ptr++: _fillbuf(p))
#undef  putc
#define putc(x,p)   (--(p)->cnt >= 0 \
                ?   x != EOF ? (x == '\n' && (p) == &_iob[1]) ? _flushbuf((x), p) : (*(p)->ptr++ = (x)) : _flushbuf((x), p) : _flushbuf((x),p))
#undef  getchar
#define getchar()   getc(stdin)
#undef  putchar
#define putchar(x)  putc((x), stdout)
#endif
int get_char(void);
void put_char(int);
void _error(char *, ...);
#endif
