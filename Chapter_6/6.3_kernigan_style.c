#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*
 Write a cross-referencer that prints
 a list of all words in a document,  and for each word,
 a list of the line numbers on which it occurs.
 Remove noise words like the, and and so on.
*/

#define MAXMALLOC 50
#define MAXNOISEWORD 100
#define MAXWORD 100
#define MAXBUF 1000
#define GARBAGEWORD 1

struct tnode {

    int *curline;
    char *word;
    int count;
    int lcounter;
    struct tnode *left;
    struct tnode *right;
};

char buf[MAXBUF];
int bufp = 0;

struct tnode *addtree(struct tnode *, char *, int *);
void treeprint(struct tnode *);
void freetree(struct tnode *);

struct tnode *talloc(void);
char *mystrdup(char *);

int strignore(int);
int comignore(int);
int getword(char *, int *, int);
int checkword(char *);

main()
{
    struct tnode *root;
    char word[MAXWORD];
    int cnewline = 1;
    int lcounter;

    root = NULL;
    while (getword(word, &lcounter, MAXWORD) != EOF)
    {
        if (isalpha(word[0])) {

            root = addtree(root, word, &cnewline);

	    if (lcounter) {

		cnewline++;
		lcounter = 0;
	    }
        }
    }

    printf("    Cross Referencer Breakdown\n");

    treeprint(root);

    freetree(root);

    free(root);
    root = NULL;

    return 0;
}

/*addtree: adding a node with word 'w' to node 'p' or down below*/

struct tnode *addtree(struct tnode *p, char *w, int *cnewline)
{
    int cond;

    if (p == NULL) { //new word received

        p = talloc(); //creating a new node

        p->curline = (int *) malloc(MAXMALLOC * sizeof(char));
	p->lcounter = 0;
	p->curline[p->lcounter] = *cnewline;
	p->lcounter++;

        p->word = mystrdup(w);
	p->count = 1;

        p->left = p->right = NULL;

    } else if ((cond = strcmp(w, p->word)) == 0) {

        p->count++; //the same word

	if (p->curline[0] != *cnewline) {

	    p->curline[p->lcounter] = *cnewline;
	    p->lcounter++;
	}

    } else if (cond < 0) { /*the smaller - to the left sub-node*/

        p->left = addtree (p->left, w, cnewline);


    } else

        p->right = addtree (p->right, w, cnewline);

    return p;
}

/*talloc: creating a node of type tnode*/
struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

char *mystrdup(char *s) /*creating a copy of string 's'*/
{
    char *p;

    int length = strlen(s);

    p = (char *) malloc(length + 1); /*+1 for '\0'*/

    if (p != NULL)

	 strcpy(p, s);

    return p;
}

int getword(char *word, int *lcounter, int limit)
{
    int getch(void);
    void ungetch(int);
    int c;
    int res;
    char *w = word;

    while (isspace(c = getch()) || c ==  '#' || c == '<' || c == '>' || c == '{' || c == '}' || c == '(' || c == ')' ||
            c == '=' || c == ';' || c == '!' || c == '?' || c == '.' || c == ',' || c == ':') {
        ;
    }

    if (c == '\"') {

        c = strignore(c);
        ungetch(c);
    }

    if (c == '/') {

        if ((c = getch()) == '/') {

            c = comignore(c);
            ungetch(c);

	} else if (c == '*') {

            c = comignore(c);
            ungetch(c);
	}
    }

    if (c != EOF) {

        *w = c;
        w++;
    }

    if (!isalpha(c)) {

        *w = '\0';
        return c;
    }


    for (; --limit > 0; w++) {

        if (!isalnum(c = getch()) && c != ' ' && c != '\'') {

	    ungetch(c);

	    if ((c = getch()) == ' ') {

		ungetch(c);

	    }
	    else {

		*w = '\n';
	    }
            break;

        } else if (c == ' ') {
	   ungetch(c);
	   break;
	}

	*w = c;
    }

    if (*w == '\n') {

	*lcounter = 1;
    }

    *w = '\0';
    w = word;

    res = checkword(w);

    if (res == GARBAGEWORD) {

	word[0] = ' ';
    }

    return word[0];
}

int getch(void)
{
    return (bufp > 0) ? buf[bufp--] : getchar();
}

void ungetch(int c)
{
    if (bufp >= MAXBUF)

        printf("ungetch: too many characters\n");

    else {

        buf[bufp] = c;
        bufp++;
    }
}

int strignore (int symbol)
{
    symbol = getch();

    while ((symbol = getch()) != '\"')
    {
        ;
    }
    symbol = ' ';

    return symbol;
}

int comignore (int symbol)
{
    if (symbol == '*') {

        symbol = getch();

        while ((symbol = getch()) != '*' && symbol != '}') {
            ;
        }

        if (symbol == '*') {

            symbol = getch();

                if (symbol == '/') {

                    symbol = ' ';
		}
                else {
                   printf ("error: comment not closed at end of file\n");
                   exit(0);
		}
	}
        else {
		printf ("error: comment not closed at end of file\n");
                exit(0);
	     }
    }
    else {

        while ((symbol = getch()) != ';') {

            ;
        }
    }
    return symbol;
}

void freetree (struct tnode *p)
{
    if (p != NULL) {

        freetree(p->left);

	free(p->curline);
	p->curline = NULL;
	free(p->word);
	p->word = NULL;
	p->count = 0;

	free(p->left);
	p->left = NULL;

        freetree(p->right);

	free(p->curline);
        p->curline = NULL;
	free(p->word);
	p->word = NULL;
	p->count = 0;

	free(p->right);
	p->right = NULL;
    }
}

/*display the tree 'p' in an alphabetic order*/
void treeprint(struct tnode *p)
{
    if (p != NULL) {

        treeprint(p->left);

	printf("%4d %s:", p->count, p->word);

	for (int i = 0; i != p->lcounter; i++) {

	    if (i == p->lcounter - 1) {

		printf(" %d;", p->curline[i]);
		break;
	    }

	    printf(" %d,", p->curline[i]);
	}

	puts("");
        treeprint(p->right);
    }
}


int checkword (char *word)
{
    static char *noisewords[MAXNOISEWORD] = {

	"the",
	"and",
	"is",
	"are",
	"to",
	"my",
	"her",
	"his",
	"your",
	"our"
    };

    for (int i = 0; i != MAXNOISEWORD && noisewords[i] != NULL; i++)
    {
	if (strcmp(word, noisewords[i]) == 0)

            return GARBAGEWORD;

    }
    return 0;
}
