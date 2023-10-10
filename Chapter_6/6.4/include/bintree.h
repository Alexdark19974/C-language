#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define BUFSIZE 1024
#define END 1
#define ERR -1
#define PREPROCESSOR 7
#define COMMENT 2
#define ASTERISK 3
#define DEFAULT_LEN 6
#define NOISE_WORD 8
#define OK 0
struct tnode {        /* the tree node */
    char *word;           /* point to the text */
    int count;            /* number of occurence */
    unsigned int lines[BUFSIZE];           /* line a document */
    struct tnode *left;   /* left child */
    struct tnode *right;  /* right child */
};

enum { PRE_ORDER = 1, IN_ORDER, POST_ORDER };
enum { NAME = 2, TYPE, QUALIFIER, PARENS, BRACKETS };

struct tnode *addtree(struct tnode *, void **, char *, int, unsigned int, unsigned int *);
void treeprint(struct tnode *, char);
void _qsort(struct tnode **tnodeCollectorP, int left, int right);
int getword(char *, int, unsigned int *);
struct tnode *talloc(void);
char *_strdup(char *);
void print_usage(void);
void free_node(struct tnode **);
void printDecreasingOrder(void **, unsigned int *);
int check_if_noise_word(char *);

