#include "bintree.h"
unsigned int get_index(unsigned int *, unsigned int);

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, void **tnodeCollectorP, char *w, int len, unsigned int line, unsigned int *idxP)
{
    int cond;
    if (p == NULL) {    /* a new word has arrived */
        p = talloc();    /* make a new node */
        tnodeCollectorP[*idxP] = p;
        *idxP+=1;
        p->word = _strdup(w);
        p->count = 1;
        memset(p->lines, 0, sizeof(p->lines));
        *p->lines = line;
        p->left = p->right = NULL;
    } else if ((cond = strncmp(w, p->word, len)) == 0) {
        p->count++;     /* reapeated word */
        p->lines[get_index(p->lines, line)] = line;
    }
    else if (cond < 0)  /* less than into left subtree */
        p->left = addtree(p->left, tnodeCollectorP, w, len, line, idxP);
    else            /* greater than into right subtree */
        p->right = addtree(p->right, tnodeCollectorP, w, len, line, idxP);
    return p;
}

/* talloc:  make a tnode */
struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

char *_strdup(char *s)   /* make a duplicate of s */
{
    char *p;

    p = (char *) malloc(strlen(s) + 1); /* +1 for '\0' */
    if (p != NULL)
        strcpy(p, s);
    return p;
}

unsigned int get_index(unsigned int *lines, unsigned int line)
{
    int idx;

    for (idx = 0; idx < BUFSIZE && lines[idx] != 0; idx++) {
        if (lines[idx] == line)
            break;
    }
    return idx;
}

