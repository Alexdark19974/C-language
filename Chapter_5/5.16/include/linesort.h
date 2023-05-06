#ifndef _LINESORT_H_
#define _LINESORT_H_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define TRUE 1
#define FALSE 0
#define ALLOCSIZE 10000 /* size of available space */
#define MAXLINES 5000        /* max #lines to be sorted */
#define MAXLEN 1000    /* max length of any input line */
#define BUFSIZE ALLOCSIZE
enum opt { NONE = 0, FOLD = 0b1, DIRECTORY_ORDER = 0b10, REVERSE = 0b100, NUMERIC = 0b1000};
char *alloc(int);
void afree(char *);
int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void _qsort(void *v[], int left, int right, int(*)(void *, void *, enum opt), enum opt);
int get_line(char *, int);
int numcmp(const char *, const char *, int);
int _strcasecmp(const char *, const char *);
int _strcmp_ext(const char *, const char *, enum opt);
int _strcmp_directory_order(const char *, const char *, int fold);
void print_usage(void);
#endif
