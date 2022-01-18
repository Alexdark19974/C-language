#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define MAXOP 100
#define MAXVAL 100
#define BUFSIZE 100
#define NUMBER '0'
#define MYEOF '1'

/*Modify getop so that it doesn’t need to use ungetch. Hint: use an internal static variable.*/

int sp = 0;
double val[MAXVAL];
char buf[BUFSIZE];
int bufp = 0;
int flag = 0;

int getop(char[]);
void push(double);
double pop(void);
int getch(void);
double stack_top(void);
void dublicate(void);
void swap(void);
void free_stack(void);

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
    static int static_c = 0;

    if (static_c == 0)
    {
        c = getch();
    }
    else
    {
        c = static_c;
        static_c = 0;
    }
   
    while ((s[0] = c) == ' ' || c == '\t') // c = 1 c = 2
    {
       c = getch();
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
        static_c = c;
    }
    else
    {
        static_c = c;
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
double stack_top(void)
{
    extern int sp;
    return val[sp - 1];
}
void dublicate(void)
{
    extern int sp;
    val[sp] = val[sp - 1];
    sp++;
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