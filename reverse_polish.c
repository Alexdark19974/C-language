#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define MAXOP 100
#define MAXVAL 100
#define BUFSIZE 100
#define NUMBER '0'
#define MYEOF '1'

int sp = 0;
double val[MAXVAL];
char buf[BUFSIZE];
int bufp = 0;
int flag = 0;

int getop(char[]);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);
double stack_top(void);
void dublicate(void);
void swap(void);
void free_stack(void);
void ungets(char[]);
/* Add commands to print the top element of the stack without popping, to duplicate it, and to swap the top two elements. Add a command to clear the stack.
*/ 
/*
Add commands for handling variables. (It’s easy to provide twenty-six variables with single-letter names.) Add a variable for the most recently printed value.*/

/*
Write a routine ungets(s) that will push back an entire string onto the input. Should ungets know about buf and bufp, or should it just use ungetch?
*/


int main(void)
{
    int type = 0;
    double op2;
    int op_2;
    int op_1;
    char s[MAXOP];
    int lock = 0;
    double variable;

    while ((type = getop(s)) != EOF)
    {
        switch(type)
        {
            case MYEOF:
            {
                printf ("\t%.8g\n", pop());
                return 0;
            }
            case 'a': case 'b' : case 'c': case 'd': case 'e': case 'f': case 'g': case 'h': case 'i': case 'j': case 'k': case 'l': case 'm': case 'n': case 'o': case 'p': case 'q': case 'r': case 's': case 't': case 'u': case 'v': case 'w': case 'x': case 'y': case 'z':
            {
                variable = pop();
                printf("the value of the latest printed variable \'%c\' is %.8g\n", (char) type, variable);
                lock = 1;
                break;
            }
            case NUMBER:
            {
                push(atof(s));
                break;
            }
            case '+':
            {
                push(pop() + pop());
                break;
            }
            case '-':
            {
                op2 = pop();
                push(pop() - op2);
                break;
            }
            case '*':
            {
                push(pop() * pop());
                break;
            }
            case '/':
            {
                op2 = pop();

                if (op2 != 0.0)
                {
                    push(pop() / op2);
                }
                else
                {
                    printf("error: zero divisor\n");
                }
                break;
            }
            case '%':
            {
                op_2 = pop();
                op_1 = pop();
                push(op_1 % op_2);
                break;
            }
            case '?':
            {
                printf("the top of the stack is %.8g\n", stack_top());
                lock = 1;
                break;
            }
            case '!':
            {
                dublicate();
                printf("%.8g is the dublicate of the stack's top %.8g\n", pop(), pop());
                lock = 1;
                break;
            }
            case '>':
            {
                swap();
                printf("the result of swap is %.8g and %.8g\n", pop(), pop());
                lock = 1;
                break;
            }
            case '#':
            {
                free_stack();
                printf("stack has been cleared\n");
                lock = 1;
                break;
            }
            case '^':
            {
                push(pow(pop(), pop()));
                break;
            }
            case '$':
            {
                push(sin(pop()));
                break;
            }
            case '@':
            {
                push(exp(pop()));
                break;
            }
            case '\n':
            {
                if (!lock)
                {
                    printf ("\t%.8g\n", pop());
                    break;
                }
            }
            default:
            {
                if (!lock)
                {
                    printf("error: unknown command %s\n", s);
                    break;        
                }
                lock = 0;
                break;
            }
        }
    }
    return 0;
}

int getop(char s[])
{
    int i = 0;
    int c = 0;

    while ((s[0] = c = getch()) == ' ' || c == '\t') // c = 1 c = 2
    {
        ;
    }
    s[1] = '\0';

    if (c == '-')
    {
        while (isdigit(s[i++] = c = getch()))
        {
            flag = -1;
        }
    }

    if (!isdigit(c) && c  != '.' && c != ' ' && c != '\t' && c != EOF)
    {
        return c;
    }
    if (isdigit(c))
    {
        while (isdigit(s[++i] = c = getch())) // c = s c = c
        {
            ;
        }
    }
    if (c == '.')
    {
        while(isdigit(s[++i] = c = getch()))
        {
            ;
        }
    }
    s[i] = '\0';

    if (c != EOF)
    {
        ungetch(c);
    }
    else
    {
        ungetch(c);

        return MYEOF;
    }
    
    return NUMBER;
}
void push(double f)
{
    if (sp < MAXVAL)
    {
       val[sp++] = (flag == -1) ? f * flag : f ; 
        flag = 0;
    }
    else
    {
        printf("error: stack full, can't push %g\n", f);
    }
}
double pop(void)
{
    if (sp > 0)
    {
        return val[--sp];
    }
    else
    {
        printf("error: stack empty\n");
        return 0.0;
    }
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
        if (c == EOF)
        {
            c = MYEOF;
        }
        else
        {
            buf[bufp++] = c;   
        }
    }
}
double stack_top(void)
{
    val[sp - 1];
}
void dublicate(void)
{
    val[sp++] = val[sp - 1];
}
void swap(void)
{
    double tmp = 0.0;
    tmp = val[0];
    val[0] = val[sp - 1];
    val[sp - 1] = tmp;
}
void free_stack(void)
{
    for (int i = 0; i <= sp; i++)
    {
        val[i] = 0;
    }
    sp = 0;
}