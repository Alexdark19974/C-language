#ifndef _HEADER_
#define _HEADER_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#define MAXLINE 1000

void display_options(void);
int get_line(char *, int);
int _atoi(char *);
int getop(char *);
int getch(void);
void ungetch(int);
int itoa(int, char *);
char * _strncat(char *, char *, unsigned int);
char * _strncpy(char *, char *, unsigned int);
int _strncmp(char *, char *, unsigned int);
int strindex(char *, char *);
int strend(char *, char *);
void reverse(char *);
#endif
