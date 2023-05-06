#include "linesort.h"

void print_usage(void)
{
    printf("Usage: \"./bin/5.17 -flndr 10\"  OR  \"./bin/5.17 -f -l -d -n -r 10\"\n");
    printf("\"-f\" - case insensitive\n");
    printf("\"-d\" - directory order (non-alphabet/digit/blank character insensitive)\n");
    printf("\"-n\" - numeric compare\n");
    printf("\"-r\" - reverse compare\n");
    printf("\"-l (num)\" - non-zero field length\n");
}
