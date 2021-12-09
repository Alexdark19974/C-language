#include <stdio.h>
#define MAXS 1000

int get_line(char[], int);
void filter (char[], char[], int);

int main(void)
{
    char string[MAXS];
    char filtered_string[MAXS];
    int length = 0;

    while ((length = get_line(string, MAXS)) > 0)
    {
        filter(filtered_string, string, length);
        printf("%s", filtered_string);
    }
    return 0;
}

void filter(char to[], char from[], int length)
{
    int i = 0;
    int round_brackets = 0;
    int square_brackets = 0;
    int parenthesis = 0;
    int single_quote = 0;
    int double_quote = 0;
    int check = 0;
    char comment = 0;

    while (from[i] != '\0')
    {
        if (from[i] == '/' && from [i + 1] == '/')
        {
            comment++;
            comment--;
            check = 1;
        }
        else if (from[i] == '/' && from[i + 1] == '*')
        {
            comment++;

            for (int i = length; i >= 0; i--)
            {
                 if (from[i] == '*' && from[i + 1] == '/')
                {
                    comment--;
                    check = 1;
                    break;
                }
            }
        }
        else if (from[i] == '/' && check != 1)
        {
            comment++;
        }
        else if (from[i - 1] == '*' && from[i] == '/' && check == 0)
        {
            comment++;
            check = 0;
        }
        else if (from[i] == '{')
        {
            parenthesis++;

            for (int i = length; i >= 0; i--)
            {
                 if (from[i] == '}')
                {
                    parenthesis--;
                    check = 1;
                    break;
                }
            }
        }
        else if (from[i] == '}' && check != 1)
        {
            parenthesis++;
            check = 0;
        }
        else if (from[i] == '(')
        {
            round_brackets++;

            for (int i = length; i >= 0; i--)
            {
                 if (from[i] == ')')
                {
                    round_brackets--;
                    check = 1;
                    break;
                }
            }
        }
        else if (from[i] == ')' && check != 1)
        {
            round_brackets++;
            check = 0;
        } 
        else if (from[i] == '[')
        {
            square_brackets++;

            for (int i = length; i >= 0; i--)
            {
                 if (from[i] == ']')
                {
                    square_brackets--;
                    check = 1;
                    break;
                }
            }
        }
        else if (from[i] == ']' && check != 1)
        {
            square_brackets++;
            check = 0;
        }
        else if (from [i] == '\'')
        {
            single_quote++;
            int single_qoute_IN = i;

            for (int i = length; i >= 0; i--)
            {
                 if (from[i] == '\'' && i != single_qoute_IN)
                {
                    single_quote--;
                    break;
                }
            }
        }
        else if (from [i] == '\"')
        {
            double_quote++;
            int double_quote_IN = i;

            for (int i = length; i >= 0; i--)
            {
                 if (from[i] == '\"' && i != double_quote_IN)
                {
                    double_quote--;
                    break;
                }
            }
        }
           
        if (single_quote == double_quote == square_brackets == round_brackets == parenthesis == 0 && comment == 0) 
        {
            to[i] = from[i];
            i++;
        }
        else
        {
            printf("Syntax error: unbalanced brackets.\n");
            to[0] = '\0';
            return;
        }
        to[i] = '\0';
    }
}

int get_line(char string[], int maxs)
{
    int i = 0;
    int c;
    int tab_count = 0;

    while (i < maxs - 2 && (c = getchar()) != EOF && c != '\n')
    {
            string[i] = c;
            i++;
    }

    if (c == '\n')
    {
        string[i] = c;
    }
    if (c == EOF)
    {
        string[i] = '\0';
        return i;
    }

    i++;
    string[i] = '\0';

    return i;    
}
