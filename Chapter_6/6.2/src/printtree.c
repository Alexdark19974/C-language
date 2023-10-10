#include "bintree.h"

/* treeprint:   in-order print of tree */
void treeprint(struct tnode *p, char mode)
{
    static char rootWord[MAXWORD] = {0};
    if (!*rootWord && p != NULL)
        strcpy(rootWord, p->word);

    if (p != NULL) {
        if (mode == IN_ORDER) {
            treeprint(p->left, mode);
            if (*rootWord != '1' && !strcmp(rootWord, p->word)) {
                printf("%4d %s ---> root\n", p->count, p->word);
                *rootWord = '1';
            } else
                printf("%4d %s\n", p->count, p->word);
            free_node(&p->left);
            treeprint(p->right, mode);
            free_node(&p->right);
        } else if (mode == PRE_ORDER) {
            if (*rootWord != '1' && !strcmp(rootWord, p->word)) {
                printf("%4d %s ---> root\n", p->count, p->word);
                *rootWord = '1';
            } else
                printf("%4d %s\n", p->count, p->word);
            treeprint(p->left, mode);
            free_node(&p->left);
            treeprint(p->right, mode);
            free_node(&p->right);
        } else if (mode == POST_ORDER) {
            treeprint(p->left, mode);
            treeprint(p->right, mode);
            if (*rootWord != '1' && !strcmp(rootWord, p->word)) {
                printf("%4d %s ---> root\n", p->count, p->word);
                *rootWord = '1';
            } else
                printf("%4d %s\n", p->count, p->word);
            free_node(&p->left);
            free_node(&p->right);
        }
    }
}

void free_node (struct tnode **p)
{
    if (*p != NULL && (*p)->word != NULL) {
        free((*p)->word);
        (*p)->word = NULL;
    }
    if (*p != NULL) {
        free(*p);
        (*p) = NULL;
    }
}

