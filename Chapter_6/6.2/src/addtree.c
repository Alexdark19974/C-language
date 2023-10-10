#include "bintree.h"

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w, int len)
{
    int cond;

    if (p == NULL) {    /* a new word has arrived */
        p = talloc();    /* make a new node */
        p->word = _strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strncmp(w, p->word, len)) == 0)
        p->count++;     /* reapeated word */
    else if (cond < 0)  /* less than into left subtree */
        p->left = addtree(p->left, w, len);
    else            /* greater than into right subtree */
        p->right = addtree(p->right, w, len);
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

