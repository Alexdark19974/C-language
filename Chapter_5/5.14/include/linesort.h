#ifndef _LINESORT_H_
#define _LINESORT_H_
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define ALLOCSIZE 10000 /* size of available space */
#define MAXLINES 5000        /* max #lines to be sorted */
#define MAXLEN 1000    /* max length of any input line */
#define BUFSIZE ALLOCSIZE
enum opt { NONE = 0, REVERSE = 0b100, NUMERIC = 0b1000 };
char *alloc(int);
void afree(char *);
int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void _qsort(void *v[], int left, int right, int(*)(void *, void *), enum opt);
int get_line(char *, int);
int numcmp(const char *, const char *);
void print_usage(void);
#endif
