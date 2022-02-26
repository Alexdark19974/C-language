#include <stdio.h>
#define MAX 100

/*Write a function escape(s,t) that converts characters like newline and tab into visible escape sequences like \n and \t as it copies the string t to s . Use a switch . Write a function for the other direction as well, converting escape sequences into the real characters. */

char escape(char[], char[]);
char reverse_escape(char[], char[]);
int get_line(char[], int);

int main(void)
{
    char from[MAX];
    char to[MAX];
    char to_1[MAX];
    int length = 0;

    while ((length = get_line(from, MAX)) > 0)
    {
        escape(to,from);
        printf("%s\n", to);
        reverse_escape(to_1, to);
        printf("%s", to_1);
    }
    return 0;
}

char reverse_escape(char to_1[], char to[])
{
    int i = 0;
    int j = 0;
    while (to[i] != '\0')
    {
        switch(to[i])
        {
            case '\\' :
            {
                switch(to[++i])
                {
                    case 'n' : 
                    {
                        to_1[j] = '\n';
                        break;
                    }

                    case 't' : 
                    {
                        to_1[j] = '\t';
                        break; 
                    }
                    
                    case '\'': 
                    {
                        to_1[j] = '\'';
                        break;
                    }
                    
                    case '\"': 
                    {
                        to_1[j] = '\"';
                        break;
                    }
                    
                    default: 
                    {
                        to_1[j] = to[--i];
                        break;
                    }
                }
            }
            ++j;
            if (to[++i] == '\\')
            {
                --i;
                break;
            }
            default :
            {
                to_1[j++] = to[i];
                break;
            } 
        }
        ++i;
    }
    to_1[j] = to[i];
}

char escape(char to[], char from[])
{
    int i = 0;
    int j = 0;
    while (from[i] != '\0')
    {
        switch(from[i])
        {
            case '\\' : 
            {
                to[j++] = '\\';
                break;
            }
            case '\n' :
            {
                to[j++] = '\\';
                to[j++] = 'n';
                break;
            }

            case '\t': 
            {
                to[j++] = '\\';
                to[j++] = 't';
                break;
            }

            case '\'' : 
            {
                to[j++] = '\\';
                to[j++] = '\'';
                break;
            }

            case '\"' : 
            {
                to[j++] = '\\';
                to[j++] = '\"';
                break;
            }

            default :
            {
                to[j++] = from[i];
                break;
            }
        }
        i++;
    }
    to[j] = '\0';
    
}
int get_line(char from[], int max)
{
    int i = 0;
    int c = 0;

    while (i < MAX - 2 && (c = getchar()) != EOF && c != '\n')
    {
        from[i] = c;
        ++i;
    }
    if (c == '\n');
    {
        from[i] = c;
        ++i;
        from[i] = '\0';
    }
    if (c == EOF)
    {
        from[i] = '\0';
        return i;
    }
    return i;
}