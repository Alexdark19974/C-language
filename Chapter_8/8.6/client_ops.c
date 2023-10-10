#include "syscalls.h"

void start_client_database(void)
{
    int c = 0;
    struct Client *head = NULL;
    static char for_bfree[MAXNAME] = {0};

    display_usage();
    while ((c = getchar()) != EOF) {
       getchar();
        switch(c - '0') {
            case ADD:
                if ((head = add_client(head)) == NULL) {
                    fprintf(stderr, "[file:%s, function:%s, line:%d]error: %s\n", __FILE__, __FUNCTION__, __LINE__, strerror(errno));
                    goto exit;
                }
                printf("Added new client: name%s, id=%u\n", head->name, head->id);
                snprintf(for_bfree, sizeof(for_bfree), "%s", head->name);
                break;
            case DELETE:
                if ((head = delete_client(head)) == NULL)
                    fprintf(stderr, "[file:%s, function:%s, line:%d] client list is empty\n", __FILE__, __FUNCTION__, __LINE__);
                break;
            case SHOW:
                if (head)
                    list_clients(head);
                display_freelist();
                break;
            case EXAMPLE:
                display_usage();
                break;
            case EXIT:
                printf("Goodbye!\n");
                goto exit;
            default:
                break;
        }
    }

exit:
        free_all(head);
        unsbrk();
}
struct Client *add_client(struct Client *head)
{
    struct Client *ptr = NULL;

    if (head == NULL) {
        head = _calloc(1, sizeof(*head));//_malloc(sizeof(*head));
        insert_client(head);
        head->next = NULL;
        return head;
    }

    ptr = _calloc(1, sizeof(*ptr));
    insert_client(ptr);
    ptr->next = head;
    head = ptr;

    return ptr;
}

struct Client *delete_client(struct Client *head)
{
    struct Client *ptr = NULL, *prevptr = NULL;
    char buf[MAXNAME] = {0};

    if (head == NULL) {
        fprintf(stderr, "warning: client list is empty!\n");
        return NULL;
    }

    printf("enter the name: ");
    fgets(buf, sizeof(buf), stdin);
    buf[strlen(buf) - 1] = '\0';

    for (ptr = head; ptr; prevptr = ptr, ptr = ptr->next) {
        if (!strcmp(ptr->name, buf)) {
            printf("found %s\n", buf);
            if (ptr == head) { // delete at the beginning
                head = ptr->next;
            } else if (prevptr->next->next == NULL) // delete at the tail 
                prevptr->next = NULL;
            else // handle the middle
                prevptr->next = ptr->next;
            _free(ptr); // return space to memalloc
            ptr = NULL;
            break;
        }
    }
    return head;
}

void insert_client(struct Client *ptr)
{
    static unsigned int idx = 1;
    char *s_ptr = NULL;
    printf("enter the name: ");
    fgets(ptr->name, sizeof(ptr->name), stdin);
    if ((s_ptr = strchr(ptr->name, '\n')) != NULL)
        *s_ptr = '\0';
    ptr->id = idx++;
}

void list_clients(struct Client *head)
{
    struct Client *ptr = head;

    for (; ptr; ptr = ptr->next)
    {
        printf("---------------\n");
        printf("idx=%u\n", ptr->id);
        printf("username:%s\n", ptr->name);
        printf("next=%p\n", (void *) ptr->next);
        printf("---------------\n");
    }
}

void display_usage(void)
{
    printf("-----------------------\n");
    printf("Press 1 - to ADD CLIENT\n");
    printf("Press 2 - to DELETE CLIENT\n");
    printf("Press 3 - to SHOW ALL CLIENTS\n");
    printf("Press 4 - to SHOW A PROMPT\n");
    printf("Press 5 - to DEALLOCATE MEMORY/EXIT\n");
    printf("-----------------------\n");
}

