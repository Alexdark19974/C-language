#include "lookup.h"

void insert(void)
{
    char name[BUFSIZE] = {0}, defn[BUFSIZE] = {0};
    NlistP p = NULL;
    int opt = 0;

    while ((opt = getword(name, defn, MAXWORD)) != EOF) {
        if (!strcmp(name, "//") || !strcmp(defn, "//"))
            continue;
        if ((p = install(name, defn, opt)) == NULL) {
            printf("Failed to install a new pair name=%s, defn=%s\n", name, defn);
            if (NESTED_DEFINE == opt)
                return;
        }
        else
            printf("New pair added: addr=%p, name=%s, defn=%s, next=%p\n", (void *) p, p->name, p->defn, (void *) p->next);
        *name = *defn = '\0';
    }
}

