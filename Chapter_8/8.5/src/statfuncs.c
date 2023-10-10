#include "syscalls.h"
#include "mydirent.h"

/*_stat: wrapper function of stat() */
int _stat(char *name, struct _stat *stbuf)
{
    int retVal;
    struct stat stTempBuf;

    if ((retVal = stat(name, &stTempBuf)) == -1)
        return retVal;

    stbuf->_st_dev = stTempBuf.st_dev;
    stbuf->_st_ino = stTempBuf.st_ino;
    stbuf->_st_mode = stTempBuf.st_mode;
    stbuf->_st_nlink = stTempBuf.st_nlink;
    stbuf->_st_uid = stTempBuf.st_uid;
    stbuf->_st_gid = stTempBuf.st_gid;
    stbuf->_st_rdev = stTempBuf.st_rdev;
    stbuf->_st_size = stTempBuf.st_size;
    memcpy((void *) &(stbuf->_st_atime), (const void *)&stTempBuf.st_atim, sizeof(stbuf->_st_atime));
    memcpy((void *) &(stbuf->_st_ctime), (const void *)&stTempBuf.st_ctim, sizeof(stbuf->_st_ctime));
    memcpy((void *) &(stbuf->_st_mtime), (const void *)&stTempBuf.st_mtim, sizeof(stbuf->_st_mtime));

    return retVal;
}

/* _fstat: wrapper function of stat() */
int _fstat(int fd, struct _stat *stbuf)
{
    int retVal;
    struct stat stTempBuf;

    if ((retVal = fstat(fd, &stTempBuf)) == -1)
        return retVal;
    stbuf->_st_dev = stTempBuf.st_dev;
    stbuf->_st_ino = stTempBuf.st_ino;
    stbuf->_st_mode = stTempBuf.st_mode;
    stbuf->_st_nlink = stTempBuf.st_nlink;
    stbuf->_st_uid = stTempBuf.st_uid;
    stbuf->_st_gid = stTempBuf.st_gid;
    stbuf->_st_rdev = stTempBuf.st_rdev;
    stbuf->_st_size = stTempBuf.st_size;
    memcpy((void *) &(stbuf->_st_atime), (const void *)&stTempBuf.st_atim, sizeof(stbuf->_st_atime));
    memcpy((void *) &(stbuf->_st_ctime), (const void *)&stTempBuf.st_ctim, sizeof(stbuf->_st_ctime));
    memcpy((void *) &(stbuf->_st_mtime), (const void *)&stTempBuf.st_mtim, sizeof(stbuf->_st_mtime));

    return retVal;
}

