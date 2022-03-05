#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKENSIZE 100
#define MAXNAMESIZE 25
#define MAXDATA_TYPESIZE 25
#define OUTSIZE 100
#define BUFSIZE 1000
#define TEMPSIZE 100

enum { NAME, PARENS, BRACKETS, TYPE };

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next available position in buf */

int get_token(void);

char token[MAXTOKENSIZE]; /*last token - лексема string*/
char name[MAXNAMESIZE]; /*the name of the (identifier)*/
char data_type[MAXDATA_TYPESIZE]; /*type of data : char, int, etc.*/
char out[OUTSIZE]; /*resulting string*/

int main(void) // convert declarations to words
{
    int type = 0;
    char temp[TEMPSIZE];

	while (get_token() != EOF) // the 1st token from string
    {
        strncpy(out, token, sizeof(out));
        temp[sizeof(out) - 1] = '\0';

        while ((type = get_token()) != '\n')
        {
            if (type == PARENS || type == BRACKETS)
            {
                strcat(out, token);
            }
            else if (type == '*')
            {
                type = get_token();

                if (type == PARENS || type == BRACKETS)
                {
                    if (type == BRACKETS)
                    {
                        snprintf(temp, sizeof(temp), "(*%s)", out);
                        strncpy(out, temp, sizeof(out) - 1);
                        temp[sizeof(temp) - 1] = '\0';
                        strcat(out, token);
                    }
                    else if (type == PARENS)
                    {
                        snprintf(temp, sizeof(temp), "(*%s)", out);
                        strncpy(out, temp, sizeof(out) - 1);
                        temp[sizeof(temp) - 1] = '\0';
                        strcat(out, token);
                    }
                }
                else if (type == TYPE)
                {
                    snprintf(temp, sizeof(temp), "%s *%s", token, out);
                    strncpy(out, temp, sizeof(out) - 1);
                    temp[sizeof(temp) - 1] = '\0';
                }
                else
                {
                    snprintf(temp, sizeof(temp), "**%s", out);
                    strncpy(out, temp, sizeof(out) - 1);
                    temp[sizeof(temp) - 1] = '\0';
                }
            }
            else if (type == TYPE)
            {
                snprintf(temp, sizeof(temp), "%s %s", token, out);
                strncpy(out, temp, sizeof(out) - 1);
                temp[sizeof(temp) - 1] = '\0';
            }
            else
            {
                printf("invalid input at %s\n", token);
            }
        }
        printf("%s\n", out);
    }
    return 0;
}

int get_token (void)
{
	int token_type = 0;
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
       buf[bufp] = c;
       bufp++;
    }
}
