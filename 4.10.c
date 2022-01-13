#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define MAXOP 100
#define MAXVAL 100
#define BUFSIZE 100
#define NUMBER '0'
#define MYEOF '1'

/*An alternate organization uses getline to read an entire input line; this makes getch and ungetch unnecessary. Revise the calculator to use this approach.*/

int sp = 0;
double val[MAXVAL];
char buf[BUFSIZE];
char f_point_buf[BUFSIZE];
int f_buf = 0;
int bufp = 0;
int flag = 0;
int i = 0;
int lock_get_line = 0;
int opening_number = 0;
int closing_number = 0;

int getop(char[]);
void push(double);
double pop(void);
double stack_top(void);
void dublicate(void);
void swap(void);
void free_stack(void);
void get_line(char[], int);

int main(void)
{
    int type = 0;
    double op2;
    int op_2;
    int op_1;
    char s[MAXOP];
    int lock = 0;
    double variable;
    double RAX = 0.0;

    while ((type = getop(s)) != EOF)
    {
        switch(type)
        {
            case MYEOF:
            {
                printf ("\t EOF : %.8g\n", pop());
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
                
                if (opening_number != (closing_number - 1) && flag != -1)
                {
                    while (opening_number < closing_number)
                    {
                        RAX = (10.0 * RAX) + (s[opening_number++] - '0');
                    }
                    printf("%.8g\n",RAX);
                    push(RAX);
                    RAX = 0.0;
                }
                else if (f_buf != 0)
                {
                   // printf("blink!\n");
                    push(atof(f_point_buf));
                    f_buf = 0;
                }
                else if (flag != -1)
                {
                    RAX = (10.0 * RAX) + (s[i - 1] - '0');
                    push(RAX);
                    RAX = 0.0;
                }
                else
                {
                    RAX = (10.0 * RAX) + (s[i - 1] - '0');
                    printf("%.8g\n",RAX);
                    push(RAX);
                    RAX = 0.0;
                }
                
                
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
                    i = 0;
                    s[i] = '\0';
                    free_stack();
                    lock_get_line = 0;
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
    if(!lock_get_line)
    {
        get_line(s,MAXOP);
        lock_get_line = 1;
    }

        if (s[i] == ' ' || s[i] == '\t')
        { 
            while (s[i] == ' ' || s[i] == '\t')
            {
                i++;
            }
        }

        if (s[i] == '-')
        {
            i++;
            flag = -1;
            while (isdigit(s[++i]))
            {
                ;
            }
        }
        
        if (!isdigit(s[i]) && s[i]  != '.' && s[i] != ' ' && s[i] != '\t' && s[i] != EOF && s[i] != '\0')
        {
            return s[i++];
        }

        if (isdigit(s[i]))
        {
            opening_number = i;

            while (isdigit(s[++i]))
            {
                ;
            }
            closing_number = i;
        }
      // printf(" the count of number is %d\n", counter);
        if (s[i] == '.')
        {
            f_point_buf[f_buf++] = s[opening_number];
            f_point_buf[f_buf++] = s[i];

            while (isdigit(s[++i]))
            {
              f_point_buf[f_buf] = s[i];
            }
        }
        
        if (s[i] == '\0') 
        {
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
void get_line(char charline[], int maxline) 
{
    int l = 0, c = 0;

    for (l = 0; --maxline > 0 && (c = getchar()) != EOF && c!= '\n';)
    {
        charline[l] = c;
        l++;
    }
    if (c == '\n')
    {
        charline[l] = c;
        l++;
    }
    charline[l] = '\0';
}
