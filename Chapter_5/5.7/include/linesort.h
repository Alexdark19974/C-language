#ifndef _LINESORT_H_
#define _LINESORT_H_
#include <stdio.h>
#include <string.h>
#define ALLOCSIZE 10000 /* size of available space */
#define MAXLINES 5000        /* max #lines to be sorted */
#define MAXLEN 1000    /* max length of any input line */
#define BUFSIZE ALLOCSIZE
char *alloc(int);
void afree(char *);
int readlines(char *lineptr[], char *linebuf, int nlines);
void writelines(char *lineptr[], int nlines);
void qsort(char *lineptrp[], int left, int right);
int get_line(char *, int);
void swap(char *[], int, int);
#endif
