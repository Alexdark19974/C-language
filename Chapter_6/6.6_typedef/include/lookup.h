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
#define NESTED_DEFINE 1
typedef char * StringP;
typedef unsigned int u_int;
typedef unsigned char u_char;
typedef struct nlist {      /* table entry */
    struct nlist *next;     /* next entry in chain */
    StringP name;             /* define name */
    StringP defn;             /* replacement text */
} Nlist, *NlistP;

void start_lookup_table(void);
NlistP install(StringP, StringP, int);
NlistP lookup(StringP);
unsigned hash (StringP);
int getword(StringP, StringP, int);
int getch(void);
void ungetch(int);
StringP _strdup(StringP);
void print_all(void);
void free_all(void);
void insert(void);
int handle_comment(u_char);

