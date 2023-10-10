#include "bintree.h"

void list_lines(unsigned int *);
/* treeprint:   in-order print of tree */
void treeprint(struct tnode *p, char mode)
{
    static char rootWord[MAXWORD] = {0};
    if (!*rootWord && p != NULL)
        strcpy(rootWord, p->word);

    if (p != NULL) {
        if (mode == IN_ORDER) {
            treeprint(p->left, mode);
                list_lines(p->lines);
            if (*rootWord != '1' && !strcmp(rootWord, p->word)) {
                printf(", count:%4d, word:%s ---> root\n", p->count, p->word);
                *rootWord = '1';
            } else
                printf(", count:%4d, word:%s\n", p->count, p->word);
            free_node(&p->left);
            treeprint(p->right, mode);
            free_node(&p->right);
        } else if (mode == PRE_ORDER) {
            list_lines(p->lines);
            if (*rootWord != '1' && !strcmp(rootWord, p->word)) {
                printf(", count:%4d, word:%s ---> root\n", p->count, p->word);
                *rootWord = '1';
            } else
                printf(", count:%4d, word:%s\n", p->count, p->word);
            treeprint(p->left, mode);
            free_node(&p->left);
            treeprint(p->right, mode);
            free_node(&p->right);
        } else if (mode == POST_ORDER) {
            treeprint(p->left, mode);
            treeprint(p->right, mode);
            list_lines(p->lines);
            if (*rootWord != '1' && !strcmp(rootWord, p->word)) {
                printf(", count:%4d, word:%s ---> root\n", p->count, p->word);
                *rootWord = '1';
            } else
                printf(", count:%4d, word:%s\n", p->count, p->word);
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

void list_lines(unsigned int *lines)
{
    int idx;
    printf("lines:");
    for (idx = 0; idx < BUFSIZE && lines[idx] != 0; idx++)
        printf(" %u", lines[idx]);
}

void printDecreasingOrder(void **tnodeCollectorP, unsigned int *idxP)
{
    struct tnode **tnodeP = (struct tnode **) tnodeCollectorP;
    unsigned int idx;

    _qsort(tnodeP, 0, *idxP - 1);

    for (idx = 0; tnodeP[idx] != NULL; idx++) {
        printf("Node address: %p\ntnodeP[%u]->word=%s;\ntnodeP[%u]->count=%d;\n", (void *) tnodeP[idx],idx, tnodeP[idx]->word, idx, tnodeP[idx]->count);
        printf("---------------------------------------\n");
    }
}

