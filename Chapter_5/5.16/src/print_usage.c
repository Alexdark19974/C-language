#include "linesort.h"

void print_usage(void)
{
    printf("Usage: \"./bin/5.16 -fdnr\"  OR  \"./bin/5.16 -f -d -n -r\"\n");
    printf("\"-f\" - case insensitive\n");
    printf("\"-d\" - directory order (non-digit/character/blank insensitive)\n");
    printf("\"-n\" - numeric compare\n");
    printf("\"-r\" - reverse compare\n");
}
