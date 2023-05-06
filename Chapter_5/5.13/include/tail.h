#ifndef _TAIL_H_
#define _TAIL_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALLOCSIZE 10000 /* size of available space */
#define MAXLINES 5000        /* max #lines to be sorted */
#define MAXLEN 1000    /* max length of any input line */
#define DEFAULTTAILLEN 10
#define BUFSIZE ALLOCSIZE
char *alloc(int);
void afree(char *);
int readlines(char *lineptr[], char *linebuf, int nlines);
int get_line(char *, int);
void tail(char **, int, int);
#endif
