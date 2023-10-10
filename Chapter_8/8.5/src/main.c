#include "syscalls.h"
#include "mydirent.h"
/*Directory entry consists of two items: a filename and its inode number */

/* print file sizes */
main(int argc, char **argv)
{
    unsigned long total_size = 0;
    if (argc == 1) {      /* default: current directory */
        display_top_info();
        display_total_bytes(&total_size);
    } else
        while (--argc > 0) {
            display_top_info();
            fsize(*++argv, &total_size);
            display_total_bytes(&total_size);
        }
    return 0;
}

