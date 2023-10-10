#ifndef _DIRENT_H_
#define _DIRENT_H_
#include "syscalls.h"
#define _NAME_MAX 14 /* longest filename component */
                            /* system-dependent */
#define BUF_SIZ 256
typedef struct {        /* portable directory entry:*/
    long ino;                   /* inode number */
    char name[_NAME_MAX+1];      /* name + '\0' terminator */
} _Dirent;

typedef struct {        /* minimal DIR: no buffering, etc. */
    int fd;                /* file descriptor for directory */
    _Dirent d;              /* the directory entry */
} _DIR;

#ifndef DIRSIZ
#define DIRSIZ  14
#endif
struct _direct   /* directory entry */
{
    ino_t d_ino;            /* inode number */
    char  d_name[DIRSIZ];   /* long name does not have '\0\' */
};

struct _stat     /* inode information returned by state */
{
    dev_t       _st_dev;     /* device of inode */
    ino_t       _st_ino;     /* inode number */
    short       _st_mode;    /* mode bits and file type */
    short       _st_nlink;   /* number of links to file */
    short       _st_uid;     /* owner's user id */
    short       _st_gid;     /* owner's group id */
    dev_t       _st_rdev;    /* for special files */
    off_t       _st_size;    /* file size in characters */
    blksize_t   _st_blksize;
    blkcnt_t    _st_blocks;
    // time_t      _st_atime;   /* time last accessed */
    // time_t      _st_mtime;   /* time last modified */
    // time_t      _st_ctime;   /* time inode last changed */
    struct timespec _st_atime, _st_mtime, _st_ctime;
};

#undef S_IFMT
#undef S_IFDIR
#undef S_IFCHR
#undef S_IFBLK
#undef S_IFREG
#define     S_IFMT 0160000      /* type of file */
#define     S_IFDIR 0040000     /* direcotry */
#define     S_IFCHR 0020000     /* character special */
#define     S_IFBLK 0060000     /* block special */
#define     S_IFREG 0100000     /* regular */

/* ... */

/* _DIR */ DIR *_opendir(char *dirname);
/* _Dirent */ struct dirent *_readdir(/*_DIR */ DIR *dfd);
void _closedir(/*_DIR */ DIR *dfd);
void fsize(char *, unsigned long *);
int _stat(char *, struct _stat *);
int _fstat(int, struct _stat *);
void dirwalk(char *, void (*fcn)(char *, unsigned long *), unsigned long *);
char *display_file_type(short);
char *display_file_perms(short);
void display_total_bytes(unsigned long *);
void display_top_info(void);
char *mystrfmt(struct timespec);
#define MAX_PATH 1024
#endif

