#include "lookup.h"

static struct nlist *hashtab[HASHSIZE]; /* pointer table */
/* install: put (name, defn) in hashtab )*/
struct nlist *install(StringP name, StringP defn, int opt)
{
    NlistP np = NULL;
    u_int hashval = 0;

    if (NESTED_DEFINE == opt) {
        if ((np = lookup(defn)) == NULL) {
            printf("error:'%s' has not been defined previously in a nested macro definition.\n", defn);
            return NULL;
        } else
            strcpy(defn, np->defn);
    }
    if ((np = lookup(name)) == NULL) {  /* not found */
        np = (NlistP) malloc(sizeof(*np));
        if (np == NULL || (np->name = _strdup(name)) == NULL) {
            printf("Failed to malloc the new entry. Reason=%s\n", strerror(errno));
            return NULL;
        }
        hashval = hash(name);
        np->next = hashtab[hashval];
        printf("Inserted at the head:\nprev head = %p, ", (void *) hashtab[hashval]);
        hashtab[hashval] = np;
        printf("curr head = %p\n", (void *) hashtab[hashval]);
    } else      /* already there */
        free((void *) np->defn);
    if ((np->defn = _strdup(defn)) == NULL)
        return NULL;
    return np;
}
StringP _strdup(StringP s)   /* make a duplicate of s */
{
    StringP p;

    p = (StringP) malloc(strlen(s) + 1); /* +1 for '\0' */
    if (p != NULL)
        strcpy(p, s);
    else
        printf("Failed to malloc the space for the name '%s'. Reason=%s\n", s, strerror(errno));
    return p;
}

/* lookup: look for s in hashtab */
NlistP lookup(StringP s)
{
    NlistP np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;  /* found */
    return NULL;        /* not found */
}

/* hash: form hash value for string s */
u_int hash(StringP s)
{
    u_int hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

void display_chain(NlistP p)
{
    for (;p != NULL ; p = p->next)
        printf("p->name=%s, p->defn=%s, p->next=%p\n", p->name, p->defn, (void *) p->next);
}

void print_all(void)
{
    u_int idx;
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
    u_int idx;
    for (idx = 0; idx < HASHSIZE; idx++)
    {
        if (hashtab[idx] != NULL) {
            NlistP temp = NULL;
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

