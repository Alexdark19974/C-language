#include "syscalls.h"

#define CHECK_NEXT_PARAM(arg, param, default_val) if (!isdigit(**(arg + 1))) { \
                                                    if (((**(arg + 1) == '-') && (*((*arg + 2)+ 1) == 'p' || *((*arg + 2) + 1) == 'o' || *((*arg + 2) + 1) == 's')) || argc == 2) { \
                                                        param = default_val; \
                                                        printf("warning: no specific number was specified so the program defaults to %d\n", default_val); \
                                                        break; \
                                                    } \
                                                    _error("error: arg %s after %s is illegal.", *(arg + 1), *arg); \
                                                    goto exit_with_failure; \
                                                  }
#if defined(FFUNC_CASE)
_FILE _iob[OPEN_MAX] = {
        { 0, (char *) 0, (char *) 0, _READ, 0 },
        { 0, (char *) 0, (char *) 0, _WRITE, 1 },
        { 0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2 }
    };
#endif

main(int argc, char **argv)
{
#if defined(LSEEK_CASE)
    params optS = { 0, 0, 0 };
    if  (argc <= 1) {
        _error("no file to read.\n");
        exit(EXIT_FAILURE);
    }
    while (--argc && *argv++ && **argv == '-') {
        switch (*++*argv) {
            case 'p':   // position in a file
                CHECK_NEXT_PARAM(argv, optS.pos, DEFAULT_POS)
                optS.pos = (int) atoi(*++argv);
                argc--;
                break;
            case 'o':   // size of data to be read
                CHECK_NEXT_PARAM(argv, optS.offset, DEFAULT_OFFSET)
                optS.offset = atoi(*++argv);
                argc--;
                break;
            case 's':   // offset (0 - START, 1 - MIDDLE - 2 END)
                CHECK_NEXT_PARAM(argv, optS.size, DEFAULT_SIZE)
                optS.size = atoi(*++argv);
                argc--;
                break;
            default:
                _error("error: unknown option \"%s\"", *argv);
                goto exit_with_failure;
        }
    }
    if (argc <= 0) {
        _error("_error: no file to read.");
        goto exit_with_failure;
    } else if (argc != 1) {
        _error("error: wrong arg %s", *argv);
        goto exit_with_failure;
    }
    read_and_print_file_at_pos(argv, optS);

    return 0;
exit_with_failure:
    exit(EXIT_FAILURE);
#elif defined (FFUNC_CASE)
    if ((*argv + 1 == NULL) || (*argv + 2 == NULL)) {
        _error("error: one or both files are missing. Can't copy.");
        goto fail;
    } else if (argc > 3) {
        _error("error: can only copy to files but you have more than 2.");
        goto fail;
    }
    if (copy(argv + 1) == ERR) // copy f1 to f2
        goto fail;
    // FILE *_iob[OPEN_MAX] = {{0}}; in case you wanted to know how to intialize local _iob to zero if it is an array of structs;
/* memset(_iob, 0, sizeof(_iob)); another way to intialize everything with zero is to use memset()
    _iob[] = {
        { 0, (char *) 0, (char *) 0, _READ, 0 },
        { 0, (char *) 0, (char *) 0, _WRITE, 1 },
        { 0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2 },
        { 0, (char *} 0, (char *) 0, 0, -1} 
        // if you don't want to use memset(), please, intialize the last unused element with zero to know if it is used or not (you will have to explicitly shift it if space is taken)
    };
    */
    __exit(); // free memory for we do not need memory leaks
    exit(EXIT_SUCCESS);
fail:
    exit(EXIT_FAILURE);
#endif
}

#if defined (LSEEK_CASE)
int read_and_print_file_at_pos(char **argv, params optS)
{
    int fd, n;
    char *bufp = NULL;

    if ((bufp = calloc(1, BUFSIZ + 1)) == NULL) {
        _error("error: faileGd to allocate memory for buffer. Reason: %s", strerror(errno));
        goto exit_with_failure;
    }

    while (*argv && (fd = open(*argv++, O_RDONLY, 0)) != -1) {
        if ((n = get(fd, bufp, optS)) < 0) {
            _error("error: error occurred while reading %s; reason=%s;\n%d bytes have been read", *argv, strerror(errno), n);
            goto exit_with_failure;
        } else write(STDOUT_FILENO, bufp, n);
        fd = 0;
    }

    if (fd == -1) {
        _error("error: error occurred while opening %s; reason=%s;", *argv, strerror(errno));
        goto exit_with_failure;
    }

    free(bufp);
    return EXIT_SUCCESS;

exit_with_failure:
    free(bufp);
    close(fd);
    return EXIT_FAILURE;
}

/* *get: read n bytes from position pos */
int get(int fd, char *buf, params optS)
{
    if (lseek(fd, optS.pos, optS.offset) >= 0) /* get to pos */
        return read(fd, buf, optS.size);
    else
        return -1;
}
/* error : print an error message and die */
#endif

#if defined(FFUNC_CASE)
_FILE *_fopen(char *name, char *mode)
{
    int fd;
    _FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;
    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
        if ((fp->flag & (_READ  | _WRITE)) == 0)
            break;          /* found free slot */
    if (fp >= _iob + OPEN_MAX)  /* no free slots */
        return NULL;
    if (*mode == 'w')
        fd = creat(name, PERMS);
    else if (*mode == 'a') {
        if ((fd = open(name, O_WRONLY, 0)) == -1)
            fd = creat(name, PERMS);
        lseek(fd, 0L, 2);
    } else
        fd = open(name, O_RDONLY, 0);
    if (fd == -1)           /* couldn't access name */
        return NULL;
    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    fp->flag = (*mode == 'r') ? _READ : _WRITE;
    return fp;
}

/* _fillbuf: allocate and fill input buffer */
int _fillbuf(_FILE *fp)
{
    int bufsize;

    if ((fp->flag & (_READ | _EOF | _ERR)) != _READ)
        return EOF;
    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
    if (fp->base == NULL)       /* no buffer yet */
        if ((fp->base = (char *) malloc(bufsize)) == NULL) // allocating bufsize + 1 is necessary if we want to store '\0' at the end of the buffer
            return EOF;        /* can't get buffer */
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
//    *(fp->ptr + bufsize) = '\0'; not necessary since only care about raw data that must be written somewhere else
    if (--fp->cnt < 0) {
        if (fp->cnt == -1)
            fp->flag |= _EOF;
        else fp->flag |= _ERR;
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char) *fp->ptr++;
}

int _fillobuf(_FILE *fp)
{
    fp->base = (char *) malloc(BUFSIZ);
    if (fp->base == NULL) {
        _error("failed to allocate memory for fp buffer");
        fp->flag |= _ERR;
        goto exit_with_failure;
    }
    fp->ptr = fp->base;
    fp->cnt = BUFSIZ - 1; // becasue one character will be pushed either way

    return EXIT_SUCCESS;
exit_with_failure:
    return EXIT_FAILURE;
}

int _flushbuf(int x, _FILE *fp)
{
    ssize_t n;

    switch(fp->fd) {
        case STDERR_FILENO:
            if (x == EOF) {
                fp->flag |= EOF;
                break;
            }
            if ((n = write(fp->fd, &x, sizeof(x)) == -1)) {
                _error("an error ocurred while writing to file descriptor %d; reason=%s", fp->fd, strerror(errno));
                fp->flag |= _ERR;
                goto exit_with_failure;
            }
            fp->cnt = 0;
            break;
        default:
            if (fp->base == NULL && x != EOF) {
                if (_fillobuf(fp) == EXIT_FAILURE)
                    goto exit_with_failure;
            } else if (x == EOF)
                return EOF;
            if ((x == '\n' && fp->fd == STDOUT_FILENO) || fp->cnt < 0) {
                if ((n = write(fp->fd, fp->base, fp->ptr - fp->base) == -1)) {
                    _error("an error ocurred while writing to file descriptor %d; reason=%s", fp->fd, strerror(errno));
                    fp->flag |= _ERR;
                    goto exit_with_failure;
                }
                fp->ptr = fp->base;
                *fp->ptr++ = x; // the left-over byte shall be added here
                fp->cnt = BUFSIZ - 1;
            } else
                *fp->ptr++ = x;
            break;
    }
    return FLUSHED;
exit_with_failure:
    return EXIT_FAILURE;
}

/* copy: ./copy file1 file2 */
int copy(char **argv)
{
    _FILE *fp1 = NULL, *fp2 = NULL;
    int c;

    if ((fp1 = _fopen(*argv, "r")) == NULL) {
        _error("failed to open %s; reason=%s", *argv, strerror(errno));
        goto exit_with_failure;
    }
    _fseek(fp1, 10, SEEK_CUR);
    if (_ferror(fp1))
        goto end;
    _fseek(fp1, -10, SEEK_CUR);
    if (_ferror(fp1))
        goto end;
    if ((*(argv + 1) != NULL) && (fp2 = _fopen(*(argv + 1), "w")) == NULL) {
        _error("failed to open %s; reason=%s", *argv, strerror(errno));
        goto exit_with_failure;
    }
    while (!_feof(fp1)) {
        c = getc(fp1);
        if (_ferror(fp1)) {
            _error("an error occurred while reading %s", *argv);
            break;
        }
        if (_fseek(fp1, 1024, SEEK_CUR) == ERR) {
            _error("error ocurred while lseek() was running; reason: %s", strerror(errno));
            fp1->flag |= ERR;
            goto exit_with_failure;
        }
        if (_ferror(fp1))
            goto end;
        putc(c, fp2 == NULL ? stdout : fp2);
        if (_ferror(fp2 == NULL ? stdout : fp2))
            break;
    }
end:
    if (ERR == _fclose(fp1))
        _error("error closing file %s; reason=%s", *argv, strerror(errno));
    else _fprintf(stderr, "closed %s\n", *argv);
    if (fp2 != NULL) {
        if (-1 == _fclose(fp2))
            _error("error closing file %s; reason=%s", *(argv + 1));
        else printf("closed %s\n", *(argv + 1));
    }
    return EXIT_SUCCESS;
exit_with_failure:
    return EXIT_FAILURE;
}

int _fclose(_FILE *fp)
{
    int retVal = 0;
    if (fp != NULL) {
        if (fp->flag & _WRITE)
            _fflush(fp);
        retVal = close(fp->fd);
        free(fp->base);
        fp->ptr = fp->base = NULL;
        fp->cnt = fp->fd = fp->flag = 0;
    }
    return retVal;
}

int _fseek(_FILE *fp, long offset, int origin)
{
    if (fp != NULL)  {
        if (fp->flag & _WRITE) {
            _fflush(fp);
            if (_ferror(fp))
                goto exit_with_failure;
            if (lseek(fp->fd, offset, origin) == ERR) {
                _error("error ocurred while lseek() was running; reason: %s", strerror(errno));
                fp->flag |= ERR;
                goto exit_with_failure;
            }
        } else {
            switch (origin) {
                case SEEK_SET:
                case SEEK_END:
                    if (lseek(fp->fd, offset, SEEK_SET) == ERR) {
                        _error("error ocurred while lseek() was running; reason: %s", strerror(errno));
                        fp->flag |= ERR;
                        goto exit_with_failure;
                    } else if (fp->flag & _READ) fp->cnt = 0;
                    break;
                case SEEK_CUR:
                    if (fp->base) {
                        fp->cnt-= offset;
                        fp->ptr+= offset;
                        if (fp->cnt < 0  || fp->cnt > BUFSIZ || (fp->flag & _EOF)) {
                                if (lseek(fp->fd, fp->flag & _EOF ? offset : fp->cnt * -1, SEEK_CUR) != ERR) // we need _EOF flag to succesfully pass _feof() function
                                    fp->cnt = 0;
                                else {
                                    _error("error ocurred while lseek() was running; reason: %s", strerror(errno));
                                    fp->flag |= ERR;
                                        goto exit_with_failure;
                                }
                        }
                    } else if (lseek(fp->fd, offset, SEEK_CUR) == ERR) {
                            _error("error ocurred while lseek() was running; reason: %s", strerror(errno));
                            fp->flag |= ERR;
                            goto exit_with_failure;
                    }
                    break;
                default:
                    _error("error: unknown request for fseek(): origin=%d", origin);
                    fp->flag |= ERR;
                    goto exit_with_failure;
            }
        }
//        fp->flag &= ~_EOF; // is it a fseek responsibility to remove the EOF flag?
//
        return OK;
    }
exit_with_failure:
    return EXIT_FAILURE;
}

void _fflush(_FILE *fp)
{
    int i;

    if (fp == NULL) { // flush it all
        for (i = 0; i < OPEN_MAX; i++) {
            if (_iob[i].flag & _WRITE && _iob[i].base) {
                if (write(_iob[i].fd, _iob[i].base, _iob[i].ptr - _iob[i].base) == ERR) {
                    _fprintf(stderr, "error: _fflush failed to perform write() properly; reason=%s\n", strerror(errno));
                    fp->flag |= ERR;
                }
                fp->cnt = fp->flag & _UNBUF ? 1 : BUFSIZ;
                fp->ptr = fp->base;
            }
        }
    } else if (fp->flag & _WRITE && (fp->base != NULL)) {
        if (write(fp->fd, fp->base, fp->ptr - fp->base) == ERR) {
            _fprintf(stderr, "error: _fflush failed to perform write() properly; reason=%s\n", strerror(errno));
            fp->flag |= ERR;
        }
        fp->cnt = fp->flag & _UNBUF ? 1 : BUFSIZ;
        fp->ptr = fp->base;
    }
}

void __exit(void)
{
    int i;

    for (i = 0; i < OPEN_MAX; i++)
        free(_iob[i].base);
}

// primitive fprintf: write args of fmt to stream
// created for fun purposes
int _fprintf(_FILE *stream, char *fmt, ...)
{
    va_list args;
    char *ptr;
    char *str, *temp_str;
    int iVal;
    va_start(args, fmt);

    for (ptr = fmt; *ptr; ptr++) {
        switch (*ptr) {
            case '%':
                switch(*++ptr) {
                    case 's':
                        str = va_arg(args, char *);
                        temp_str = str;
                        for (temp_str = str; *temp_str; temp_str++)
                            putc(*temp_str, stream);
                        break;
                    case 'd':
                        iVal = va_arg(args, int);
                        putc(iVal, stream);
                    default:
                        putc('%', stream);
                        putc(*ptr, stream);
                        break;
                }
                break;
            default:
                putc(*ptr, stream);
                break;
        }
    }
    va_end(args);
    return OK;
}
#endif

void _error(char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    //fprintf(stderr, "error: ");
    printf("error:");
    vprintf(fmt, args);
    printf("\n");
    //vfprintf(stderr, fmt, args);
    //fprintf(stderr,"\n");
    va_end(args);
}

