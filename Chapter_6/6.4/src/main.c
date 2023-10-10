#include "bintree.h"

/* word frequency count */
main(int argc, char **argv)
{
    struct tnode *root;
    void *tnodeCollectorP[BUFSIZE] = { NULL };
    char word[MAXWORD], mode = IN_ORDER;
    int len = DEFAULT_LEN;
    unsigned int line_cnt = 1, idx = 0;
    root = NULL;
    while(argc-- > 1 && ++argv) {
        if (**argv == '-' && *(*argv + 1) == '-') {
            *argv+=2;
            if (!strcmp(*argv, "pre-order"))
                mode = PRE_ORDER;
            else if (!strcmp(*argv, "in-order"))
                mode = IN_ORDER;
            else if (!strcmp(*argv, "post-order"))
                mode = POST_ORDER;
            else if (!strncmp(*argv, "wlength=", strlen("wlength="))) {
                *argv+=strlen("wlength=");
                    while(**argv != '\0' && !isdigit(**argv)) ++*argv;
                    if (**argv == '\0') {
                        printf("error: wlength must be followed by '=' sign and a number.\n");
                        goto error;
                    }
                    printf("wlength=%c\n", **argv);
                    len = **argv - '0';
            }
            else {
                printf("error: unknown parameter '%s'\n", *argv);
                goto error;
            }
        } else if (**argv == '-') {
            if (*++*argv == 'w' && *++*argv == 'l') {
                while(!isdigit(*++*argv)) ;
                if (**argv == '\0') {
                    printf("error: wlength must be followed by '=' sign and a number.\n");
                    goto error;
                }
                printf("wl=%c\n", **argv);
                len = **argv - '0';
            } else {
                printf("error: unknown parameter '%s'\n", *argv);
                goto error;
            }
        }
    }
/*    printf("len=%d\n", len); */
    while (getword(word, MAXWORD, &line_cnt) != EOF) {
        if (isalpha(word[0]))
            root = addtree(root, tnodeCollectorP, word, len, line_cnt, &idx);
        else if (isdigit(word[0]))
            printf("warning: digits are not supported in this program.\n");
        else if (word[0] == '#')
            printf("warning: preprocessor constants are ignored.\n");
    }
    printDecreasingOrder(tnodeCollectorP, &idx);
    if (mode == PRE_ORDER)
        printf("######## Pre-order traversal ########\n");
    else if (mode == IN_ORDER)
        printf("######## In-order traversal ########\n");
    else if (mode == POST_ORDER)
        printf("######## Post-order traversal ########\n");
    if (root == NULL) {
        printf("error: the root is %p\n", (void *) root);
        goto error;
    }
    treeprint(root, mode);
    free_node(&root);
    return 0;
error:
    print_usage();
    return EXIT_FAILURE;
}

void print_usage(void)
{
    printf("'./bin/bintree --pre-order -wl=6'\n \
            './bin/bintree --post-order --wlength=6'\n \
            './bin/bintree --wlength=6'\n \
            './bin -wl=6'\n \
            './bin/bintree'\n");
}


/* qsort:  sort v[left]...v[right] into decreasing order */
void _qsort(struct tnode **tnodeCollectorP, int left, int right)
{
    int i, last;
    void swap(struct tnode **, int i, int j);
    if (left >= right)    /* do nothing if array contains */
        return;           /* fewer than two elements */
    swap(tnodeCollectorP ,left, (left + right)/2);
    last = left;
    for(i = left + 1; i <= right; i++)
        if ((tnodeCollectorP[i]->count > tnodeCollectorP[left]->count))
            swap(tnodeCollectorP, ++last, i);
    swap(tnodeCollectorP ,left, last);
    _qsort(tnodeCollectorP, left, last-1);
    _qsort(tnodeCollectorP , last+1, right);
}

/* swap:  interchange v[i] and v[j] */
void swap(struct tnode **tnodeCollectorP, int i, int j)
{
    struct tnode *temptnodeP = NULL;

    temptnodeP = tnodeCollectorP[i];
    tnodeCollectorP[i] = tnodeCollectorP[j];
    tnodeCollectorP[j] = temptnodeP;
}

