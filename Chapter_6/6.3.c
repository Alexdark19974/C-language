#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <malloc.h>

/*
 Write a cross-referencer that prints
 a list of all words in a document,  and for each word,
 a list of the line numbers on which it occurs.
 Remove noise words like the, and and so on.
*/

#define MALLOC_SIZE 50
#define NOISE_WORDS_SIZE 100
#define MAX_WORD_SIZE 100
#define BUF_SIZE_MAX 1000
#define GARBAGE_WORD 1

struct tree_node
{
    int *current_line;
    char *word;
    int word_count;
    int line_counter;
    struct tree_node *left;
    struct tree_node *right;
};

char buf[BUF_SIZE_MAX] = {0};
int bufp = 0;

struct tree_node *add_tree(struct tree_node *, char *, int *);
void tree_print(struct tree_node *);
void free_tree(struct tree_node *);

struct tree_node *tree_alloc(void);
char *my_strdup(char *);

int string_ignore(int);
int comment_ignore(int);
int get_word(char *, int *, int);
int check_word(char *);

int main(void)
{
    struct tree_node *root = NULL;
    char word[MAX_WORD_SIZE] = {0};
    int catch_new_line = 1;
    int line_counter = 0;

    while (get_word(word, &line_counter, MAX_WORD_SIZE) != EOF)
    {
        if (isalpha(word[0]))
        {
            root = add_tree(root, word, &catch_new_line);

	    if (line_counter)
	    {
		catch_new_line++;
		line_counter = 0;
	    }
        }
    }

    printf("    Cross Referencer Breakdown\n");
    tree_print(root);

    free_tree(root);

    free(root);
    root = NULL;

    return 0;
}

/*addtree: adding a node with word 'w' to node 'p' or down below*/

struct tree_node *add_tree(struct tree_node *p, char *w, int *catch_new_line)
{
    int condition = 0;

    if (p == NULL) //new word received
    {
        p = tree_alloc(); //creating a new node

        p->current_line = (int *) malloc(MALLOC_SIZE * sizeof(char));
	p->line_counter = 0;
	p->current_line[p->line_counter] = (int) *catch_new_line;
	p->line_counter++;

        p->word = my_strdup(w);
	p->word_count = 1;

        p->left = p->right = NULL;
    }
    else if ((condition = strcmp(w, p->word)) == 0)
    {
        p->word_count++; //the same word

	if (p->current_line[0] != *catch_new_line)
	{
	    p->current_line[p->line_counter] = *catch_new_line;
	    p->line_counter++;
	}
    }
    else if (condition < 0) /*the smaller - to the left sub-node*/
    {
        p->left = add_tree (p->left, w, catch_new_line);
    }
    else
    {
        p->right = add_tree (p->right, w, catch_new_line);
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

int get_word(char *word, int *line_counter, int limit)
{
    int getch(void);
    void ungetch(int);
    int c = 0;
    int res = 0;
    char *w = word;

    while (isspace(c = getch()) || c ==  '#' || c == '<' || c == '>' || c == '{' || c == '}' || c == '(' || c == ')' ||
            c == '=' || c == ';' || c == '!' || c == '?' || c == '.' || c == ',' || c == ':')
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
	c = getch();

        if (!isalnum(c) && c != ' ' && c != '\'')
        {
	    ungetch(c);

	    if ((c = getch()) == ' ')
	    {
		ungetch(c);
	    }
	    else
	    {
		*w = '\n';
	    }

            break;
        }
	else if (c == ' ')
	{
	   ungetch(c);
	   break;
	}

	*w = c;
    }

    if (*w == '\n')
    {
	*line_counter = 1;
    }

    *w = '\0';
    w = word;

    res = check_word(w);

    if (res == GARBAGE_WORD)
    {
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

	free(p->current_line);
	p->current_line = NULL;
	free(p->word);
	p->word = NULL;
	p->word_count = 0;

	free(p->left);
	p->left = NULL;

        free_tree(p->right);

	free(p->current_line);
        p->current_line = NULL;
	free(p->word);
	p->word = NULL;
	p->word_count = 0;

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

	printf("%4d %s:", p->word_count, p->word);

	for (int i = 0; i != p->line_counter; i++)
	{
	    if (i == p->line_counter - 1)
	    {
		printf(" %d;", p->current_line[i]);
		break;
	    }

	    printf(" %d,", p->current_line[i]);
	}

	puts("");
        tree_print(p->right);
    }
}


int check_word (char *word)
{
    static char *noise_words[NOISE_WORDS_SIZE] =
    {
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

    for (int i = 0; i != NOISE_WORDS_SIZE && noise_words[i] != NULL; i++)
    {
	if (strcmp(word, noise_words[i]) == 0)
        {
            return GARBAGE_WORD;
        }
    }
    return 0;
}
