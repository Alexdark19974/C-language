#include "lookup.h"

void start_lookup_table(void)
{
    enum { INSERT_HEAD = 1, INSERT_TAIL, SEARCH, DELETE, PRINT_ALL, EXIT, PROMPT};
    char opt = 0;
    printf("Choose an option: 1 - insert at the head, 2 - insert at the tail, 3 - search, 4 - delete, 5 - print all, 6 - exit, 7 - show prompt\n");

    while (1) {
        putchar(':');
        opt = getchar() - '0';
        getchar();
        switch(opt) {
            case INSERT_HEAD:
            case INSERT_TAIL:
            case SEARCH:
            case DELETE /* UNDEF */:
                insert(opt);
                break;
            case PRINT_ALL:
                print_all();
                break;
            case PROMPT:
                display_prompt();
                break;
            case EXIT:
                goto exit;
            default:
                printf("Unknown command.\n");
                display_prompt();
                break;
        }
    }
exit:
    free_all();
}

