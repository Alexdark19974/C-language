#include "syscalls.h"
#include "mydirent.h"

/*fsize: print size of file "name" */
void fsize(char *name, unsigned long *total_size)
{
    struct _stat stbuf;
    if (_stat(name, &stbuf) == -1) {
        fprintf(stderr, "fsize: can't access %s\n", name);
        return;
    }
    if ((stbuf._st_mode & S_IFMT) == S_IFDIR)
        dirwalk(name, fsize, total_size);
    if ((stbuf._st_mode & S_IFMT) != S_IFDIR) // we ignore directories unlike "ls"
        *total_size = *total_size + stbuf._st_size;

    printf("%s:\t%s\t%d:\t%d:\t%ld:\t%s\t%s\t%s\t%s\n", display_file_type(stbuf._st_mode), display_file_perms(stbuf._st_mode), \
            stbuf._st_uid, stbuf._st_gid, stbuf._st_size, \
            mystrfmt(stbuf._st_atime), mystrfmt(stbuf._st_mtime), mystrfmt(stbuf._st_ctime), name);
}

// mystrfmt: format data from timespec struct into human-readable string
char * mystrfmt(struct timespec ts)
{
    static char mybuf[257] = {0};
    struct tm tmp_tm;

    if (!gmtime_r(&ts.tv_sec, &tmp_tm)) {
        fprintf(stderr, "failed to gmtime_r'ed time\n");
        return "unknown";
    }
    if (!strftime(mybuf, 255, "%Y-%m-%dT%H:%M:%S", &tmp_tm)) {
        fprintf(stderr, "Failed to convert time into human-readable format!\n");
        return "unknown";
    }

    return mybuf;
}

