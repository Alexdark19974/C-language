#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define BUFSIZE 1024
#define END 1
#define ERR -1
#define PREPROCESSOR 7
#define ASTERISK 3
struct key {
    char *word;
    int count;
};

int getword(char *, int);
#ifndef STRUCTPTR
int binsearch(char *, struct key *, int);
#else
struct key *binsearch(char *, struct key *, int);
#endif

