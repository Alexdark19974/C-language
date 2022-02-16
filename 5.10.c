  
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define MAXOP 100
#define MAXVAL 100
#define BUFSIZE 100
#define NUMBER '0'
#define MYEOF '1'

/*
Write the program expr , which evaluates a reverse Polish expression from the command line, where each operator or operand is a separate argument. For example,
expr 2 3 4 + *
evaluates 2 X (3 + 4).
*/

int sp = 0;
double val[MAXVAL];
char buf[BUFSIZE];
char s[MAXVAL];
int bufp = 0;
int flag = 0;
int close_get_line = 0;


int getop(char *);
void push(double);
double pop(void);
void get_line(char *, int);
double stack_top(void);
void dublicate(void);
void swap(void);
void free_stack(void);

int main(int argc, char *argv[])
{
    printf("argc %d \n", argc);
    return 0;
    int type = 0;
    double op2;
    int op_2;
    int op_1;
    char s[MAXOP];
    int lock = 0;
    double variable;


    while (--argc > 0 && (type = getop(*++argv)))
    {
        printf("argc %d \n", argc);
        printf("type is %c \n", type);
        switch (type)
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
                printf("1) argv is %s\n", *argv);
                printf("2) atofed argv is %lf\n", atof(*argv));
                printf("3 ) flag is %d\n", flag);

                double number = atof(*argv);
                push(number);
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
                return EOF;
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
    printf ("\t%.8g\n", pop());
    return 0;
}

int getop(char *argv)
{
    if (*argv == '-')
    {
        printf("is MINUS\n");

        if (isdigit(*++argv))
        {
            flag = -1;
        }
    }
    
    if (!isdigit(*argv) && *argv  != '.' && *argv != ' ' && *argv != '\t' && *argv != EOF)
    {
        return *argv;
    }

    if (isdigit(*argv))
    {
        while (isdigit(*++argv)) // c = s c = c
        {
           ;
        }
    }

    /*if (*argv  == '.')
    {
        while(isdigit(s[length]))
        {
            length++;
        }
        length--;
    } */
    return NUMBER;
}

void push(double f)
{
    if (sp < MAXVAL)
    {
       val[sp] = f; 

       if (val[sp] == -0.0)
       {
           val[sp] = 0.0;
       }

       sp++;
       flag = 0;
       printf("push: %lf\n", val[sp - 1]);
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

double stack_top(void)
{
    return val[sp - 1];
}
void dublicate(void)
{
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

void get_line(char *charline, int maxlen) 
{
    int c = 0;

    for (; --maxlen > 0 && (c = getchar()) != EOF && c!= '\n';)
    {
        *charline++ = c;
    }
    if (c == '\n')
    {
        *charline++ = c;
        *charline = '\0';
    }
    if(c == EOF)
    {
       *charline = '\0';
    }
}