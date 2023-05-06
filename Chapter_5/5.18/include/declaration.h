#ifndef _DECLARATION_H_
#define _DECLARATION_H_
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define  MAXTOKEN   100
#define BUFSIZE     1000
#define TRUE 1
#define FALSE 0
#define ERR -1
enum { NAME = 2, TYPE, PARENS, BRACKETS };

void dcl(void);
void dirdcl(void);
int gettoken(void);
int type_name_check(char *);
#endif
