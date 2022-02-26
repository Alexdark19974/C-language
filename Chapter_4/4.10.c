  
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
char s[MAXVAL];
int bufp = 0;
int flag = 0;
int close_get_line = 0;


int getop(char[]);
void push(double);
double pop(void);
void get_line(char *, int);
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
    char buff_line[MAXVAL];

    while ((type = getop(buff_line)) != EOF)
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
                push(atof(buff_line));
                printf("%s s is buff_line\n", buff_line);
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
                if (close_get_line || !lock)
                {
                    printf ("\t%.8g\n", pop());
                    close_get_line = 0;
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

int getop(char buff_line[])
{
    extern int close_get_line;
    int i = 0;
    int c = 0;
    static int length = 0;

    if (!close_get_line)
    {
        get_line(s, MAXVAL);
        close_get_line = 1;
        length = 0;
    }
    
    while ((buff_line[0] = c = s[length]) == ' ' || c == '\t') // c = 1 c = 2
    {
        length++;
    }
    printf ("c is %c\n", c);

    if (c == '\n')
    {
        printf("'\\n' is found\n");
    }
    buff_line[1] = '\0';

    if (c == '-')
    {
        length++;
        while (isdigit(buff_line[i] = c = s[length]))
        {
            flag = -1;
            i++;
            length++;
        }
    }

    if (!isdigit(c) && c  != '.' && c != ' ' && c != '\t' && c != EOF)
    {
        printf("%c is non-integer\n", c);
        length++;
        return c;
    }
    if (isdigit(c))
    {
        while (isdigit(buff_line[i] = c = s[length])) // c = s c = c
        {
            length++;
            i++;
        }
    }

    /*if (c == '.')
    {
        length++;
        while(isdigit(s[length]))
        {
            length++;
        }
        length--;
    } */
    
    buff_line[i] = '\0';
    return NUMBER;
}

void push(double f)
{
    if (sp < MAXVAL)
    {
       val[sp] = (flag == -1) ? f * flag : f; 

       if (val[sp] == -0.0)
       {
           val[sp] = 0.0;
       }

       sp++;
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