#include "lookup.h"

void insert(char opt)
{
    char name[BUFSIZE] = {0}, defn[BUFSIZE] = {0};
    struct nlist *p = NULL;
    char sym = 0;
    if (opt == SEARCH || opt == DELETE) {
        printf("Insert the name to search/delete: ");
        if (getword(name, MAXWORD) != EOF) {
            if (opt == SEARCH) {
                if ((p = lookup(name)) == NULL)
                    printf("Failed to find entry for '%s'.\n", name);
                else
                    printf("Found the entry: addr=%p, name=%s, defn=%s, next=%p\n", (void *) p, p->name, p->defn, (void *) p->next);
            } else if (opt == DELETE)
                delete_node(name); /* undef function */
            else
                exit(EXIT_FAILURE);
            return;
        }
    }
    printf("Example:\nname: code, defn: 1921681732\n");
    printf("Enter an entry via 1) space between a name and a defn or 2) via a newline char\n");

    putchar(':');
    do {
next:
        if (getword(name, MAXWORD) != EOF)
            if (!strcmp(name, "//"))
                break;
        do {
            if (getword(defn, MAXWORD) != EOF) {
                if (!strcmp(defn, "//"))
                    break;
                if ((p = install(name, defn, opt)) == NULL)
                    printf("Failed to install a new pair name=%s, defn=%s\n", name, defn);
                else
                    printf("New pair added: addr=%p, name=%s, defn=%s, next=%p\n", (void *) p, p->name, p->defn, (void *) p->next);
            }
            if (isspace((sym = getch())) && sym != '\n') {
                ungetch(sym);
                goto next;
            }
            ungetch(sym);
        } while (0);
    } while (0);
}

