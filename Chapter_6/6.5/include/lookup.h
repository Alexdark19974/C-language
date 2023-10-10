#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#define MAXWORD 100
#define BUFSIZE 1024
#define END 1
#define CONTINUE 5
#define ERR -1
#define PREPROCESSOR 7
#define COMMENT 2
#define ASTERISK 3
#define DEFAULT_LEN 6
#define NOISE_WORD 8
#define OK 0
#define HASHSIZE 101
enum { INSERT_HEAD = 1, INSERT_TAIL, SEARCH, DELETE, EXIT, PROMPT};

struct nlist {      /* table entry */
    struct nlist *next;     /* next entry in chain */
    char *name;             /* define name */
    char *defn;             /* replacement text */
};

void start_lookup_table(void);
struct nlist *install(char *, char *, char);
struct nlist *lookup(char *);
unsigned hash (char *s);
int getword(char *, int);
int getch(void);
void ungetch(int);
char *_strdup(char *);
void print_all(void);
void free_all(void);
void delete_node(char *);
void display_prompt(void);
void insert(char);
int handle_comment(unsigned char);

