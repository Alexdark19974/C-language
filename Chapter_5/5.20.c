#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_TOKEN_SIZE 100
#define MAX_BUF_SIZE 1000
#define MAX_TOKEN_SIZE 100
#define MAX_NAME_SIZE 100
#define MAX_QUALIFIER_SIZE 100
#define MAX_MODIFIER_SIZE 100
#define MAX_DATA_TYPE_SIZE 100
#define MAX_OUT_SIZE 100

enum { NAME, PARENS, BRACKETS, TYPE, QUALIFIER, MODIFIER, };

char buf[MAX_BUF_SIZE];
int bufp = 0;

void dcl(void);
void dirdcl(void);

int get_token(void);
int token_type = 0; /*type of char*/
char token[MAX_TOKEN_SIZE]; /*last token - лексема string*/
char name[MAX_NAME_SIZE]; /*the name of the (identifier)*/
char qualifier[MAX_QUALIFIER_SIZE];
char modifier[MAX_MODIFIER_SIZE];
char data_type[MAX_DATA_TYPE_SIZE]; /*type of data : char, int, etc.*/
char out[MAX_OUT_SIZE]; /*resulting string*/

int main(void) // convert declarations to words

{
    while (get_token() != EOF) // the 1st token from string
    {
        switch (token_type)
        {
            case TYPE:
            {
                strncpy(data_type, token, sizeof(data_type) - 1);
                data_type[sizeof(data_type) - 1] = '\0';
                break;
            }
            case QUALIFIER:
            {
                strncpy(qualifier, token, sizeof(qualifier) - 1);
                qualifier[sizeof(qualifier) - 1] = '\0';
                break;
            }
            case MODIFIER:
            {
                strncpy(modifier, token, sizeof(modifier) - 1);
                modifier[sizeof(modifier) - 1] = '\0';
                break;
            }
            default:
            {
                printf("error: missing type\n");
                return 0;
            }
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
        if (qualifier[0] != '\0' && modifier[0] == '\0')
        {
            printf("%s: %s %s %s\n", name, out, qualifier, data_type);
        }
        else if (qualifier[0] == '\0' && modifier[0] != '\0')
        {
            printf("%s: %s %s %s\n", name, out, modifier, data_type);
        }
        else if (qualifier[0] == '\0' && modifier[0] == '\0')
        {
            printf("%s: %s %s %s %s\n", name, out, qualifier, modifier, data_type);
        }
        else
        {
            printf("%s: %s %s\n", name, out, data_type);
        }

        token_type = 0;
        qualifier[0] = '\0';
        modifier[0] = '\0';
    }
    return 0;
}

/*parse a declarator*/
void dcl (void)
{
    int ns = 0;

   if (token_type == '\n')
    {
        return;
    }

    for (ns = 0; get_token() == '*';) // counting '*'
    {
        ns++;
    }

    dirdcl();

    if(token_type == '*')
    {
        ns++;
    }

    while (ns-- > 0)
    {
        strcat(out, " pointer to");
    }
}

/*parse a direct declarator*/
void dirdcl (void)
{
    int type = 0;
    void ungetch(int);

    switch (token_type)
    {
        case '(':
        {
            dcl();

            if (token_type != ')')
            {
                printf("error: missing ')'\n");
                exit(0);
            }
            break;
        }
        case ')':
        {
            return;
        }
        case ']':
        {
            return;
        }
        case NAME:
        {
            strncpy(name, token, sizeof(name) - 1);
            name[sizeof(name) - 1] = '\0';
            break;
        }
        case TYPE:
        {
            strncpy(data_type, token, sizeof(data_type) - 1);
            data_type[sizeof(data_type) - 1] = '\0';
            break;
        }
        case QUALIFIER:
        {
            strncpy(data_type, token, sizeof(data_type) - 1);
            data_type[sizeof(data_type) - 1] = '\0';
            strcpy(qualifier, token);
            break;
        }
        case MODIFIER:
        {
            strncpy(modifier, token, sizeof(modifier) - 1);
            modifier[sizeof(modifier) - 1] = '\0';
            break;
        }
        default:
        {
            if (isdigit(token_type))
            {
                printf("error: number at the beginning of dcl not allowed\n");exit(0);
           }
            else
            {
                printf("error: expected name or (dcl)\n");
                exit(0);
            }
            break;
        }
    }

    while ((type = get_token()) == PARENS || type == BRACKETS || type == NAME ||type == '(' || type == '*' || type == MODIFIER)
    {

        switch (type)
        {
            case NAME:
            {
                strncpy(name, token, sizeof(name) - 1);
                name[sizeof(name) - 1] = '\0';
                break;
            }
            case PARENS:
            {
                strcat(out, " function returning");
                break;
            }
            case MODIFIER:
            {
                strncpy(modifier, token, sizeof(modifier) - 1);
                modifier[sizeof(modifier) - 1] = '\0';
                break;
            }
            case BRACKETS:

            {
                strcat(out, " array ");
                strcat(out, token);
                strcat(out, " of");
                break;
            }
            case '*':
            {
                ungetch(type);
                dcl();
            }

            case '(':
            {
                dcl();
            }
            default:
            {
                break;
            }
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

    if (token_type == '\n')
    {
        return token_type;
    }

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
        *ptr = c;
        ptr++;

        for (*ptr = c; (*ptr = getch()) != ']' && *ptr != '\n';)
        {
            ptr++;
        }
        if (*ptr != ']')
        {
            printf ("error: missing ']'\n");
            exit(0);
        }

        ++ptr;
        *ptr = '\0';

        return token_type = BRACKETS;
    }
    else if (isalpha(c))
    {
        *ptr = c;
        ptr++;

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

        if (*ptr == '\n')
        {
            ungetch(*ptr);
        }

        *ptr = '\0';

        ptr = token;

        if (strcmp("char", ptr) == 0 || strcmp("int", ptr) == 0 || strcmp("double", ptr) == 0 || strcmp("long", ptr) == 0 || strcmp("float", ptr) == 0 || strcmp("void", ptr) == 0)
        {
            return token_type = TYPE;
        }
        if (strcmp("const", ptr) == 0 || strcmp("volatile", ptr) == 0 || strcmp("static", ptr) == 0 || strcmp("auto", ptr) == 0 || strcmp("register", ptr) == 0)
        {
            return token_type = QUALIFIER;
        }
        if (strcmp("signed", ptr) == 0 || strcmp("unsigned", ptr) == 0)
        {
            return token_type = MODIFIER;
        }

        return token_type = NAME;
    }
    return token_type = c;
}

int getch(void)
{
    --bufp;
    return (bufp > 0) ? buf[bufp] : getchar();
}
void ungetch(int c)
{
    if (bufp >= MAX_BUF_SIZE)
    {
        printf("ungetch: too many characters\n");
    }
    else
    {
        buf[bufp] = c;
        bufp++;
    }
}
