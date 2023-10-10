#include "syscalls.h"
#include "mydirent.h"

/* dirwalk: apply fcn to all files in dir */
void dirwalk(char *dir, void (*fcn)(char *, unsigned long *total_size), unsigned long *total_size)
{
    char name[MAX_PATH];
   /* _Dirent */ struct dirent *dp;
    /* _DIR */ DIR *dfd;

    if ((dfd = _opendir(dir)) == NULL) {
        fprintf(stderr, "dirwalk: can't open %s\n", dir);
        return;
    }
    while ((dp = _readdir(dfd)) != NULL) {
        if (strcmp(dp->d_name, ".") == 0
         || strcmp(dp->d_name, "..") == 0)
            continue;   /* skip self and parent */
        if (strlen(dir) + strlen(dp->d_name) + 2 > sizeof(name))
            fprintf(stderr, "dirwalk: name %s/%s too long\n", dir, dp->d_name);
        else {
            sprintf(name, dir[strlen(dir) -1] == '/' ? "%s%s" : "%s/%s", dir, dp->d_name);
            (*fcn)(name, total_size); // recursively walk and enter fcn until a non-directory file is met, then print it recursively.
        }
    }
    _closedir(dfd);
}

/* opendir: open a directory for readdir calls */
/*_DIR */DIR *_opendir(char *dirname)
{
    int fd;
    struct _stat stbuf;
    /*_DIR */ DIR *dp;
 // if ((dp = opendir(dirname))) // does the same thing
    if ((dp = fdopendir((fd = open(dirname, O_RDONLY, 0)))) == NULL
     || _fstat(fd, &stbuf) == -1
     || (stbuf._st_mode & S_IFMT) != S_IFDIR
     /* || (dp = (_DIR *) malloc(sizeof(_DIR))) == NULL */) {
        if (fd == -1) fprintf(stderr, "error while opening %s; reason=%s\n", dirname, strerror(errno));
        return NULL;
    }
#if 0
    dp->fd = fd;
    /* extra info for a directory entry */
    dp->d.ino = stbuf._st_ino;
    snprintf(dp->d.name, sizeof(dp->d.name), "%s", dirname);
#endif
    return dp;
}

/* closedir: close directory opened by opendir */
void _closedir(/*_DIR */DIR *dp)
{
    closedir(dp);
#if 0
    if (dp) {
        close(dp->fd);
        free(dp);
    }
#endif
}

/* readdir: read directory entries in sequence */
/*_Dirent*/ struct dirent *_readdir(/*_DIR*/DIR *dp)
{
#if 0
    struct _direct dirbuf; /* local directory structure */
    static _Dirent d;       /* return portable structure */
#endif
    struct dirent *dirBuf; /*standard directory structure: system independent from dirent.h */
    while ((dirBuf = readdir(dp)))
        return dirBuf;
#if 0 // this will not work: read https://stackoverflow.com/questions/36144807/why-does-linux-use-getdents-on-directories-instead-of-read
    while (read(dp->fd, (char *) &dirbuf, sizeof(dirbuf)) == sizeof(dirbuf)) {
        if (dirbuf.d_ino == 0)      /* slot not in use */
            continue;
        d.ino = dirbuf.d_ino;
        strncpy(d.name, dirbuf.d_name, DIRSIZ);
        d.name[DIRSIZ] = '\0';  /* ensure termination */
        return &d;
    }
#endif
    return NULL;
}

