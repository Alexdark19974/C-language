#include "syscalls.h"
#if defined(COPY_FILE) || defined (CAT_FILE)
#define PERMS 0666  /* RW fir owner, group, others */

int cat_file(int, char *);

/* cp: copy f1 to f2 */
main(int argc, char *argv[])
{
#ifndef CAT_FILE
    int f1, f2, n;
    char buf[BUFSIZ];
    if (argc != 3)
        _error("Usage: cp from to");
    if ((f1 = open(argv[1], O_RDONLY, 0)) == -1)
        _error("cp: can't open %s", argv[1]);
    if ((f2 = creat(argv[2], PERMS)) == -1) // creat() will truncate file to zero if it exists or create a file if it doesn't exist.
        _error("cp: can't create %s, mode %03o", argv[2], PERMS);
    while ((n = read(f1, buf, BUFSIZ)) > 0)
        if (write(f2, buf, n) != n)
            _error("cp: write error on file %s", argv[2]);
#else
    if (argc <= 1) {
        _error("cat: no file to cat");
        exit(EXIT_FAILURE);
    }
    int fd = 0, retVal = 0;
    char buf[BUFSIZ] = {0};
    while (--argc && (fd = open(*++argv, O_RDONLY, 0)) != -1) {
        retVal = cat_file(fd, buf);
        close(fd);
        if (retVal == -1)
            exit(EXIT_FAILURE);
    }
    if (argc && fd == -1) {
        _error("an error occurred opening file %s", *argv);
        exit(EXIT_FAILURE);
    }
#endif
#else
main(void) /* copy input ot output */
{
#ifndef READWRITE_BUFFERED
    int n;
#endif

#if (defined(READWRITE) || !defined(READWRITE)) && !defined(READWRITE_WRAPPED) && !defined (READWRITE_BUFFERED)
    char buf[BUFSIZ];
    while ((n = read(0, buf, BUFSIZ)) > 0)
        write(1, buf, n);
#elif defined (READWRITE_WRAPPED)
#if defined (READWRITE_BUFFERED)
    printf("buffered getchar()\n");
#endif
    while ((n = get_char()) > 0)
        put_char(n);
#endif
#endif
    return 0;
}
#if defined (READWRITE_WRAPPED) && !defined (READWRITE_BUFFERED)
/* getchar: unbuffered single character input */
int get_char(void)
{
    char c;

    return (read(0, &c, 1) == 1) ? (unsigned char) c : EOF;
}
#elif defined (READWRITE_BUFFERED)
int get_char(void)
{
    static char buf[BUFSIZ];
    static char *bufp = buf;
    static int n = 0;
    if (n == 0) {   /* buffer is empty */
        n = read(0, buf, sizeof buf);
        bufp = buf;
    }
    return (--n >= 0) ? (unsigned char) *bufp++ : EOF;
}
#endif

void put_char(int c)
{
    write(1, &c, 1);
}

#if defined(COPY_FILE) || defined(CAT_FILE)
/* error : print an error message and die */
void _error(char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    fprintf(stderr, "error: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr,"\n");
    va_end(args);
    exit(1);
}
#endif
#ifdef CAT_FILE
int cat_file(int fd, char *buf)
{
    int nbytes = 0;
    while ((nbytes = read(fd, buf, BUFSIZ)) > 0)
        if (write(1, buf, nbytes) == -1) {
            _error("an error occurred while writing.\n");
            return nbytes = -1;
        }
    return nbytes;
}
#endif

