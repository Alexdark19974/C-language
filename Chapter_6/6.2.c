#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <malloc.h>

/*Write a program that reads a C program and prints in alphabetical order each group of variable names that are identical in the first 6 characters but different somewhere thereafter. Don't count words within strings and comments. Make 6 a parameter that can be set from the command line.*/

#define MAX_WORD_SIZE 100
#define BUF_SIZE_MAX 1000
#define STRUCT_ELEMENT_SIZE (sizeof(reserved_word) / sizeof(struct key_word))
#define IS_NOT_VARIABLE 0
#define IS_KEY_WORD 1
#define IS_VARIABLE 2

struct tree_node
{
    char *word;
    int count;
    struct tree_node *left;
    struct tree_node *right;
};

struct key_word
{
    char *word;
};

char buf[BUF_SIZE_MAX] = {0};
int bufp = 0;

struct tree_node *add_tree(struct tree_node *, char *, int);
void tree_print(struct tree_node *);
void free_tree(struct tree_node *);
struct tree_node *tree_alloc(void);
char *my_strdup(char *);
int check_if_key_word(struct key_word*, char *, int);
int string_ignore(int);
int comment_ignore(int);
int get_word(struct key_word*, char *, int, int);

int main(int argc, char **argv)
{
    struct tree_node *root = NULL;
    char word[MAX_WORD_SIZE] = {0};
    struct key_word reserved_word[] =
    {
        {"char"},
        {"short"},
        {"int"},
        {"float"},
        {"double"},
        {"long"},
    };
    int N = STRUCT_ELEMENT_SIZE;
    static int strcmp_len = 0;

    --argc;
    ++argv;

    if (argc > 0 && isdigit(*(*argv)))
    {
        strcmp_len = atoi (*argv);
    }
    if (!argc)
    {
	puts("can't work. Please, insert the parameter when launching the program.");
	exit(-1);
    }

    while (get_word(reserved_word, word, MAX_WORD_SIZE, N) != EOF)
    {
        if (isalpha(word[0]))
        {
            root = add_tree(root, word, strcmp_len);
        }
    }

    tree_print(root);

    free_tree(root);

    free(root);
    root = NULL;

    return 0;
}

/*addtree: adding a node with word 'w' to node 'p' or down below*/

struct tree_node *add_tree(struct tree_node *p, char *w, int strcmp_len)
{
    int condition = 0;

    if (p == NULL) //new word received
    {
        p = tree_alloc(); //creating a new node
        p->word = my_strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    }
    else if ((condition = strncmp (w, p->word, strcmp_len)) == 0)
    {
        p->count++; //the same word
    }
    else if (condition < 0) /*the smaller - to the left sub-node*/
    {
        p->left = add_tree (p->left, w, strcmp_len);
    }
    else
    {
        p->right = add_tree (p->right, w, strcmp_len);
    }
    return p;
}

/*talloc: creating a node of type tnode*/
struct tree_node *tree_alloc(void)
{
    return (struct tree_node *) malloc(sizeof(struct tree_node));
}

char *my_strdup(char *s) /*creating a copy of string 's'*/
{
    char *p = NULL;

    int length = strlen(s);

    p = (char *) malloc(length + 1); /*+1 for '\0'*/

    if (p != NULL)
    {
        strncpy(p, s, length);
	p[length] = '\0';
    }

    return p;
}

int get_word(struct key_word *reserved_word, char *word, int limit, int N)
{
    int getch(void);
    void ungetch(int);
    int c = 0;
    char *w = word;

    while (isspace(c = getch()) || c ==  '#' || c == '<' || c == '>' || c == '{' || c == '}' || c == '(' || c == ')' || c == '=' || c == ';')
    {
        ;
    }

    if (c == '\"')
    {
        c = string_ignore(c);
        ungetch(c);
    }

    if (c == '/')
    {
        if ((c = getch()) == '/')
        {
            c = comment_ignore(c);
            ungetch(c);
        }
        else if (c == '*')
        {

            c = comment_ignore(c);
            ungetch(c);
        }
    }

    if (c != EOF)
    {
        *w = c;
        w++;
    }

    if (!isalpha(c))
    {
        *w = '\0';
        return c;
    }

    limit--;
    for (; limit > 0; w++, limit--)
    {
        if (!isalnum(*w = getch()) && *w != '.' && *w != '_')
        {
            ungetch(*w);
            break;
        }
    }

    *w = '\0';
    w = word;

    int res = 0;

    if ((res = check_if_key_word(reserved_word, w, N)) == IS_KEY_WORD)
    {
        get_word(reserved_word, word, limit, N);
    }
    else if (res == IS_NOT_VARIABLE)
    {
        get_word(reserved_word, word, limit, N);
    }
    return word[0];
}

int getch(void)
{
    return (bufp > 0) ? buf[bufp--] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUF_SIZE_MAX)
    {
        printf("ungetch: too many characters\n");
    }
    else
    {
        buf[bufp] = c;
        bufp++;
    }
}

int check_if_key_word (struct key_word *reserved_word, char *s, int N)
{
    struct key_word *ptr = reserved_word;

    for (; ptr < (reserved_word + N); ptr++)
    {
        if (strcmp(ptr->word, s) == 0)
        {

            return IS_KEY_WORD;
        }
    }

    if (strcmp(s, "main") == 0 || strcmp(s, "void") == 0
    || strcmp(s, "return") == 0 || strcmp(s, "include") == 0 || strcmp (s, "stdio.h") == 0 || strcmp (s, "stdlib.h") == 0)
    {
        return IS_NOT_VARIABLE;
    }

    return IS_VARIABLE;
}

int string_ignore (int symbol)
{
    symbol = getch();

    while ((symbol = getch()) != '\"')
    {
        ;
    }
    symbol = ' ';

    return symbol;
}

int comment_ignore (int symbol)
{
    if (symbol == '*')
    {
        symbol = getch();

        while ((symbol = getch()) != '*' && symbol != '}')
        {
            ;
        }

        if (symbol == '*')
        {
            symbol = getch();

                if (symbol == '/')
                {
                    symbol = ' ';
                }
                else
                {
                   printf ("error: comment not closed at end of file\n");
                   exit(0);
                }
            }
            else
            {
                printf ("error: comment not closed at end of file\n");
                exit(0);
            }
    }
    else
    {
        while ((symbol = getch()) != ';')
        {
            ;
        }
    }
    return symbol;
}

void free_tree (struct tree_node *p)
{
    if (p != NULL)
    {
        free_tree(p->left);

	free(p->word);
	p->word = NULL;
	p->count = 0;

	free(p->left);
	p->left = NULL;

        free_tree(p->right);

	free(p->word);
	p->word = NULL;
	p->count = 0;

	free(p->right);
	p->right = NULL;
    }
}

/*display the tree 'p' in an alphabetic order*/
void tree_print(struct tree_node *p)
{
    if (p != NULL)
    {
        tree_print(p->left);
        printf("%4d %s\n", p->count, p->word);
        tree_print(p->right);
    }
}
