#ifndef _DECLARATION_H_
#define _DECLARATION_H_
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <setjmp.h>
#define  MAXTOKEN   100
#define BUFSIZE     1000
#define TRUE    1
#define FALSE   0
#define ERR -   7
#define COMMA   3
enum { NONE = 0x0, NAME = 0x2, TYPE = 0x4, PARENS = 0x8, BRACKETS = 0x10, FUNCTION = 0x20, ENCAP_TOKEN = 0x40, SKIP_TOKEN = 0x80, ASTERISK = 0x100};

int gettoken(int);
int type_name_check(char *);
void peek(int *);
int peektoken(int);
int iterate_through(int);
int check_next_params(int);
int check_brackets(int);
int check_function_params(int);
int check_name_or_type(int);
void clear_buffers(char *, char *, char *, char *, char *, char *, int *);
int parse(void);
void print_usage(void);
int print_error(char *, int);
int getch(void);
void ungetch(int);
#endif
