#include "syscalls.h"
#include "mydirent.h"

void display_top_info(void)
{
    printf("%s\t%s\t\t%s\t%s\t%s\t%s\t\t\t%s\t\t\t%s\t\t\t%s\n", "FTYPE", "PERMS", "UID", "GID", "SIZE", "ACCESS", "MODIFY", "CHANGE", "NAME");
}

void display_total_bytes(unsigned long *total_size)
{
    printf("------------------------------\ntotal=%lu bytes\n\n", *total_size);
    *total_size = 0; // make it zero to avoid value accumulation
}

// display_file_perms: read file_mode and make a string containing permissions akin to "ls"
char *display_file_perms(short file_mode)
{
    static char buf[_NAME_MAX] = {""};
    int i;
    *buf = '\0'; // a trick to force strcat() to concatenate from the beginning
    for (i = 0; i < 3; i++)
    {
        if (i == 0) {
            strcat(buf, file_mode & S_IRUSR ? "r" : "-");
            strcat(buf, file_mode & S_IWUSR ? "w" : "-");
            strcat(buf, file_mode & S_IXUSR ? "x" : "-");
        } else if (i == 1) {
            strcat(buf, file_mode & S_IRGRP ? "r" : "-");
            strcat(buf, file_mode & S_IWGRP ? "w" : "-");
            strcat(buf, file_mode & S_IXGRP ? "x" : "-");
        } else {
            strcat(buf, file_mode & S_IROTH ? "r" : "-");
            strcat(buf, file_mode & S_IWOTH ? "w" : "-");
            strcat(buf, file_mode & S_IXOTH ? "x" : "-");
        }
    }

    return buf;
}

// display_file_type: read file_mode and return file type
char *display_file_type(short file_mode)
{
    switch (file_mode & S_IFMT) {
        case S_IFREG:
            return "f";
        case S_IFDIR:
            return "d";
        case S_IFLNK:
            return "l";
        case S_IFCHR:
            return "c";
        case S_IFBLK:
            return "b";
        default:
            return "unknown";
    }
}

