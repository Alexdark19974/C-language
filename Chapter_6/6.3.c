#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define BUF_SIZE 1000

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

char buf[BUF_SIZE] = {0};
int bufp = 0;

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);

int main()
{
    struct tnode *root;
    char word[MAXWORD];

    root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
	    root = addtree(root, word);
    treeprint(root);
    return 0;
}

struct tnode *talloc(void);
char *mystrdup(char *);

/*addtree: adding a node with word 'w' to node 'p' or down below*/

struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;

    if (p == NULL) { //new word received
	p = talloc(); //creating a new node
	p->word = mystrdup(w);
	p->count = 1;
	p->left = p->right = NULL;
    } else if ((cond = strcmp (w, p->word)) == 0)
	p->count++; //the same word
    else if (cond < 0) /*the smaller - to the left sub-node*/
	p->left = addtree (p->left, w);
    else
	p->right = addtree (p->right, w);
    return p;
}

/*display the tree 'p' in an alphabetic order*/
void treeprint(struct tnode *p)
{
    if (p != NULL) {
	treeprint(p->left);
	printf("%4d %s\n", p->count, p->word);
	treeprint(p->right);
    }
}

#include <stdlib.h>

/*talloc: creating a node of type tnode*/
struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

char *mystrdup(char *s) /*creating a copy of string 's'*/
{
    char *p;

    p = (char *) malloc(strlen(s)+1); /*+1 for '\0'*/
    if (p != NULL)
	strcpy(p,s);
    return p;
}

int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch())) //not getchar() here
     ;
    if (c != EOF)
     *w++ = c;
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }
    for (; --lim > 0; w++)
     if (!isalnum(*w = getch())) {
         ungetch(*w);
         break;
     }
    *w = '\0';
    return word[0];
}

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}
void ungetch(int c)
{
    if (bufp >= BUF_SIZE)
    {
        printf("ungetch: too many characters\n");
    }
    else
    {
        buf[bufp++] = c;
    }
}
