#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXTOKEN 100
#define BUFSIZE 1000

enum {NAME, PARENS, BRACKETS, TYPE};

char buf[BUFSIZE];
int bufp = 0;


void dcl(void);
void dirdcl(void);

int get_token(void);
int token_type = 0; /*type of char*/
char token[MAXTOKEN]; /*last token - лексема string*/
char name[MAXTOKEN]; /*the name of the (identifier)*/
char data_type[MAXTOKEN]; /*type of data : char, int, etc.*/
char out[1000]; /*resulting string*/

int main(void) // convert declarations to words
{
    while (get_token() != EOF) // the 1st token from string
    {
        if (token_type == TYPE)
        {
             strcpy(data_type, token); //data type
        }
        else
        {
            printf("error: missing type\n");
            return 0;
        }
        out[0] = '\0';

        dcl(); // parsing the rest of the string

        if (token_type != '\n')
        {
            if (token_type == ')')
            {
                printf("error: missing '('\n");
                exit(0);
            }
            else if (token_type == ']')
            {
                printf("error: missing '['\n");
                exit(0);
            }
            else
            {
                printf ("syntax error\n");
                exit(0);
            }
        }

        printf("%s: %s %s\n", name, out, data_type);
    }
    return 0;
}

/*parse a declarator*/
void dcl (void)
{
    int ns = 0;

    for (ns = 0; get_token() == '*';) // counting '*'
    {
        ns++;
    }

    dirdcl();

    while (ns-- > 0)
    {
        strcat (out, " pointer to");
    }
}

/*parse a direct declarator*/

void dirdcl (void)
{
    int type = 0;

    if (token_type == '(')
    {
        dcl();

        if (token_type != ')')
        {
            printf("error: missing ')'\n");
            exit(0);
        }
    }
    else if (token_type == NAME) /*variable name*/
    {
        strcpy(name, token);
    }
    else if (token_type != ')' && token_type != ']' && token_type != NAME)
    {
        if (isdigit(token_type))
        {
              printf("error: number at the beginning of dcl not allowed\n");
              exit(0);
        }
        else
        {
            printf("error: expected name or (dcl)\n");
            exit(0);
        }
    }
    else if (token_type == ']' || token_type == ')')
    {
        return;
    }
    
    while ((type = get_token()) == PARENS || type == BRACKETS)
    {
        if (type == PARENS)
        {
            strcat(out, " function returning");
        }
        else if (type == BRACKETS)
        {
            strcat(out, " array ");
            strcat(out, token);
            strcat(out, " of");
        }
    }
}

int get_token (void)
{
    int c = 0;
    int getch(void);
    void ungetch(int);
    char *ptr = token;
    static int first_round_bracket = 0;

    while ((c = getch()) == ' ' || c == '\t')
    {
        ;
    }
    if (c == '(')
    {
        first_round_bracket = 1;

        if ((c = getch()) == ')')
        {
            strcpy(token, "()");
            first_round_bracket = 0;

            return token_type = PARENS;
        }
        else
        {
            if (!isalnum(c) && c != '*')
            {
                printf("error: missing ')'\n");
                exit(0);
            }

            ungetch(c);

            return token_type = '(';
        }
    }
    else if (c == '[')
    {
        *ptr++ = c;

        for (*ptr = c; (*ptr = getch()) != ']' && *ptr != '\n';)
        {
            ptr++;
        }

        if (*ptr != ']')
        {
          printf ("error: missing ']'\n");
          exit(0);
        }

        *++ptr = '\0';

        return token_type = BRACKETS;
    }
    else if (isalpha(c))
    {
        *ptr++ = c;

        for (*ptr = c; (*ptr = getch()) != ' ' && *ptr != ')' && *ptr != ']' && *ptr != '\n'; ptr++)
        {
            switch (*ptr)
            {
                case '(':
                {
                    first_round_bracket = 1;
                    ungetch(*ptr);

                    *ptr = '\0';
                    
                    return token_type = NAME; 
                }
                case '[':
                {
                    ungetch(*ptr);
                    
                    *ptr = '\0';
                    
                    return token_type = NAME;
                }
            }
        }
 
        if (*ptr == ']')
        {
            return token_type = *ptr;
        }
        else if (*ptr == ')')
        {
            if (!first_round_bracket)
            {
                return token_type = *ptr;
            }
            else
            {
                ungetch(*ptr);
                *ptr = '\0';
                first_round_bracket = 0;
                return token_type = NAME;
            }
        }

        *ptr = '\0';
        ptr = token;

        if (strcmp("char", ptr) == 0|| strcmp("int", ptr) == 0 || strcmp("double", ptr) == 0 || strcmp("long", ptr) == 0 || strcmp("float", ptr) == 0 || strcmp("void", ptr) == 0)
        {
            return token_type = TYPE;
        }
        return token_type = NAME;
    }
    return token_type = c;
}

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
    {
        printf("ungetch: too many characters\n");
    }
    else
    {
        buf[bufp++] = c;   
    }
}