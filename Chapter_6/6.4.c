#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <malloc.h>

/*
 Write a C Program that prints
 the distinct words in its input
 sorted into decreasing order of frequency of occurrence.
 Precede each word by its count.
*/

#define MAX_WORD_SIZE 100
#define BUF_SIZE_MAX 1000
#define TALLOC_COLLECTOR_SIZE 500
#define PTR_ARR_SIZE 500
struct tnode
{
    char *word;
    int word_count;
    struct tnode *left;
    struct tnode *right;
};

struct array
{
    struct tnode *node;
};

char buf[BUF_SIZE_MAX] = {0};
int bufp = 0;

char *ptr_arr[PTR_ARR_SIZE] = {NULL};
int ptr_arr_counter = 0;
struct tnode *talloc_collector[TALLOC_COLLECTOR_SIZE] = {NULL};
int talloc_collector_counter = 0;

struct tnode *addtree(struct tnode *, char *, int *, struct array *);
void free_tree(void);
void q_sort (struct array *, int, int);

struct tnode *talloc(void);
char *my_strdup(char *);

int string_ignore(int);
int comment_ignore(int);
int getword(char *, int);

int main(void)
{
    struct tnode *root = NULL;
    char word[MAX_WORD_SIZE] = {0};
    int n_nodes = 0;
    struct array arr[100] = {NULL};

    while (getword(word, MAX_WORD_SIZE) != EOF)
    {
        if (isalpha(word[0]))
        {
            root = addtree(root, word, &n_nodes, arr);
        }
    }

    q_sort(arr, 0, n_nodes - 1);

    puts("sorted words using qsort by the descending order: ");

    for (int i = 0; i < n_nodes; i++)
    {
	printf("%d : %s\n", arr[i].node->word_count, arr[i].node->word);
    }

    free_tree();

    return 0;
}

/*addtree: adding a node with word 'w' to node 'p' or down below*/

struct tnode *addtree(struct tnode *p, char *w, int *n_nodes, struct array *arr)
{
    int cond = 0;

    if (p == NULL) //new word received
    {
        p = talloc(); //creating a new node
        p->word = my_strdup(w);
	p->word_count = 1;
        p->left = p->right = NULL;
	arr[*n_nodes].node = p;
	*n_nodes+=1;
	talloc_collector[talloc_collector_counter] = p;
	talloc_collector_counter++;
    }
    else if ((cond = strcmp(w, p->word)) == 0)
    {
        p->word_count++; //the same word
    }
    else if (cond < 0) /*the smaller - to the left sub-node*/
    {
        p->left = addtree (p->left, w, n_nodes, arr);
    }
    else
    {
        p->right = addtree (p->right, w, n_nodes, arr);
    }
    return p;
}

/*talloc: creating a node of type tnode*/
struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

char *my_strdup(char *s) /*creating a copy of string 's'*/
{
    char *p = NULL;
    int length = strlen(s);

    p = (char *) malloc(length + 1); /*+1 for '\0'*/
    ptr_arr[ptr_arr_counter] = p;
    ptr_arr_counter++;
    if (p != NULL)
    {
        strncpy(p, s, length);
	p[length] = '\0';
    }

    return p;
}

int getword(char *word, int limit)
{
    int getch(void);
    void ungetch(int);
    int c = 0;
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

    *w = '\0';
    w = word;

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

void free_tree (void)
{
    for (int i = 0; i != ptr_arr_counter; i++)
    {
        if (isalpha(*ptr_arr[i]))
        {
            free(ptr_arr[i]);
            ptr_arr[i] = NULL;
        }
    }

    for (int i = 0; i != talloc_collector_counter; i++)
    {
        free(talloc_collector[i]);
        talloc_collector[i] = NULL;
    }
}

void q_sort (struct array *arr, int left, int right)
{
    int i = 0;
    int last = 0;
    void swap (struct array *arr, int i, int j);

    if (left >= right)
    {
        return;
    }

 /*
 {N} - pivot element
 [N] - swap target
 (N) - counter element
 [3] 4 5 {9} 1 2 4 ---> {9} 4 5 3 1 2 4 ---> {9} (4) 5 3 1 2 4 ---> {9} 4 (5) 3 1 2 4 ---> {9} 4 5 (3) 1 2 4 ---> {9} 4 5 3 (1) 2 4 ---> {9} 4 5 3 1 (2) 4 ---> {9} 4 5 3 1 2 (4)

 partitioning into 2 parts:
 1) 9 (no need to sort because 9 is the greatest number)
 2) 4 5 3 1 2 4
 second round:

 [4] 5 {3} 1 2 4 ---> {3} 5 4 1 2 4 ---> {3} (5) 4 1 2 4 ---> {3} [(5)] 4 1 2 4 ---> {3} 5 (4) 1 2 4 ---> {3} 5 [(4)] 1 2 4 ---> {3} 5 4 (1) 2 4 ---> {3} 5 4 1 (2) 4 ---> {3} 5 4 1 2 (4)
 {3} 5 4 [1] 2 (4) ---> {3} 5 4 4 2 1 ---> {3} 5 4 [4] 2 1 ---> 4 5 4 3 2 1

 partitioning into 2 parts:
 1) 4 5 4
 2) 3 2 1 (no need to sort because the order is as it should be)

 third round:

 [4] {5} 4 ---> {5} (4) 4 ---> {5} 4 (4)

 fourth round:

 all partitions sorted, no need to go deeper

 the resulting string:

 9 5 4 4 3 2 1

*/
    swap (arr, left, ((left + right) / 2));

    last = left;

    for (i = left + 1; i <= right; i++)
    {
	if (arr[i].node->word_count > arr[left].node->word_count)
        {
            swap(arr, ++last, i);
        }
    }

    swap (arr, left, last);

    q_sort(arr, left, last - 1);
    q_sort(arr, last + 1, right);
}

void swap (struct array *arr, int i, int j)
{
    if (i == j)
    {
	return;
    }

    struct tnode *temp = talloc();
    temp->word = my_strdup(arr[i].node->word);
    temp->word_count = arr[i].node->word_count;
    temp->left = arr[i].node->left;
    temp->right = arr[i].node->right;

    arr[i].node->word = my_strdup(arr[j].node->word);
    arr[i].node->word_count = arr[j].node->word_count;
    arr[i].node->left = arr[j].node->left;
    arr[i].node->right = arr[j].node->right;

    arr[j].node->word = my_strdup(temp->word);
    arr[j].node->word_count = temp->word_count;
    arr[j].node->left = temp->left;
    arr[j].node->right = temp->right;

    free(temp);
}

