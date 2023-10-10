#include "lookup.h"
#include <string.h>

static struct nlist *hashtab[HASHSIZE]; /* pointer table */
/* install: put (name, defn) in hashtab )*/
struct nlist *install(char *name, char *defn, char opt)
{
    struct nlist *np = NULL;
    unsigned hashval = 0;

    if ((np = lookup(name)) == NULL) {  /* not found */
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = _strdup(name)) == NULL) {
            printf("Failed to malloc the new entry. Reason=%s\n", strerror(errno));
            return NULL;
        }
        hashval = hash(name);
        if  (opt == INSERT_HEAD) {
insert_head:
            np->next = hashtab[hashval];
            printf("Inserted at the head:\nprev head = %p, ", (void *) hashtab[hashval]);
            hashtab[hashval] = np;
            printf("curr head = %p\n", (void *) hashtab[hashval]);
        } else if (opt == INSERT_TAIL) {
            if (hashtab[hashval] != NULL) {
                struct nlist *temp = NULL;
                for (temp = hashtab[hashval]; temp->next != NULL ; temp = temp->next) ;
                printf("Inserted at the tail:\nprev tail = %p, next=%p, ", (void *) temp,(void *) temp->next);
                temp->next = np;
                printf("curr tail = %p, next=%p, ", (void *) temp->next,(void *) temp->next->next);
            } else {
                printf("No tail because no head. Head and tail will be equal.\n");
                goto insert_head;
            }
        }
    } else      /* already there */
        free((void *) np->defn);
    if ((np->defn = _strdup(defn)) == NULL)
        return NULL;
    return np;
}
char *_strdup(char *s)   /* make a duplicate of s */
{
    char *p;

    p = (char *) malloc(strlen(s) + 1); /* +1 for '\0' */
    if (p != NULL)
        strcpy(p, s);
    else
        printf("Failed to malloc the space for the name '%s'. Reason=%s\n", s, strerror(errno));
    return p;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s)
{
    struct nlist *np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;  /* found */
    return NULL;        /* not found */
}

/* hash: form hash value for string s */
unsigned hash(char *s)
{
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

void display_chain(struct nlist *p)
{
    for (;p != NULL ; p = p->next)
        printf("p->name=%s, p->defn=%s, p->next=%p\n", p->name, p->defn, (void *) p->next);
}

void print_all(void)
{
    unsigned int idx;
    for (idx = 0; idx < HASHSIZE; idx++) {
         printf("hashtab[%d]: addr=%p\n", idx, (void *) hashtab[idx]);
         if (hashtab[idx] != NULL) {
             printf("-----------------\n");
             display_chain(hashtab[idx]);
             printf("-----------------\n");
         }
    }
}

void free_all(void)
{
    unsigned int idx;
    for (idx = 0; idx < HASHSIZE; idx++)
    {
        if (hashtab[idx] != NULL) {
            struct nlist *temp = NULL;
            while (hashtab[idx] != NULL) {
                temp = hashtab[idx];
                hashtab[idx] = hashtab[idx]->next;
                free(temp->name);
                temp->name = NULL;
                free(temp->defn);
                temp->defn = NULL;
                free(temp);
                temp = NULL;
            }
        }
    }
}

/* undef: delete an entry in the lookup table */
void delete_node(char *name)
{
    unsigned hashval;
    struct nlist *curr = NULL, *prev = NULL;
    hashval = hash(name);
    curr = hashtab[hashval];
    while (curr != NULL) {
        if (!strcmp(name, curr->name)) {
            printf("delete the entry: addr=%p, name=%s, defn=%s, next=%p.\n", (void *) curr, curr->name, curr->defn, (void *) curr->next);
            free(curr->name);
            curr->name = NULL;
            free(curr->defn);
            curr->defn = NULL;
            if (prev == NULL && curr->next != NULL) {
                printf("Rechained prev entry at the head: was =%p,", (void *) hashtab[hashval]);
                hashtab[hashval] = curr->next;
                printf("now =%p.\n", (void *) hashtab[hashval]);
            } else if (prev != NULL && curr->next == NULL) {
                printf("Rechained prev entry at the tail: was =%p,", (void *) curr);
                prev->next = curr->next;
                printf("now =%p.\n", (void *) hashtab[hashval]);
            } else if (prev != NULL && curr->next != NULL) {
                printf("Rechained prev entry in the middle: was =next->%p,", (void *) prev->next);
                prev->next = curr->next->next;
                printf("now =next->%p.\n", (void *) prev->next);
            }
            if (hashtab[hashval] == curr) {
                free(hashtab[hashval]);
                hashtab[hashval] = NULL;
            } else {
                free(curr);
                curr = NULL;
            }
            break;
        }
        prev = curr;
        curr = curr->next;
    }
}

