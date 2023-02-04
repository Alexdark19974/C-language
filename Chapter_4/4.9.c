#include <stdio.h>
#include <stdlib.h>  /* for atof() */
#include <math.h>

#define MAXOP   100  /* max size of operand or operator */
#define NUMBER  '0'  /* signal that a number was found */
#define MODULUS '%'
#define PRINT_TOP 't'
#define CLEAR_STACK 'c'
#define COSINUS 'C'
#define SINUS 'S'
#define EXPONENT 'e'
#define DUPLICATE_STACK 'd'
#define POW '^'
int getop(char []);
void push(double);
double pop(void);
void print_top(void);
void clear_stack(void);
void duplicate_stack(void);
int handle_variables(int c );
int is_EOF = 0;
/* reverse Polish calculator */
main()
{
    int type;
    double op2;
    char s[MAXOP];

    printf(": ");
    while ((type = getop(s)) != EOF) {
        switch (type) {
            case PRINT_TOP:
                print_top();
                printf(": ");
                break;
            case CLEAR_STACK:
                clear_stack();
                printf(": ");
                break;
            case DUPLICATE_STACK:
                duplicate_stack();
                printf(": ");
                break;
            case COSINUS:
                push(cos(pop()));
                break;
            case SINUS:
                push(sin(pop()));
                break;
            case EXPONENT:
                push(exp(pop()));
                break;
            case POW:
                op2 = pop();
                push(pow(pop(), op2));
                break;
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case  '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: zero divisor\n");
                break;
            case MODULUS:
                /* the data after the floating point will be discarded */
                op2 = pop();
                push((int)pop() % (int)op2);
                break;
            case '\n':
                printf("\t= %.8g\n", pop());
                if (!is_EOF)
                    printf(": ");
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
        if (is_EOF)
            break;
    }
    return 0;
}

#define MAXVAL  100  /* maximum depth of val stack */

int sp = 0;          /* next free stack position */
double val[MAXVAL];  /* value stack */

/* push:  push f onto value stack */
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

/* pop:  pop and return top value from stack */
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf ("error: stack empty\n");
        return 0.0;
    }
}

#include <ctype.h>

int getch(void);
void ungetch(int);

/* getop:  get next character or numeric operand */
int getop(char s[])
{
    int i, c, sym, is_variable;
    while ((s[0] = c = getch()) == ' ' || c == '\t')
       ;
    s[1] = '\0';
    is_variable = handle_variables(c);
    sym = c = s[0] = is_variable;
    i = 0;
    if (sym == '-' && !isdigit(s[++i] = c = getch())) {
        ungetch(c);
        return sym;
    }
    if ((tolower(sym) == 't') && (c = getch()))
        return PRINT_TOP;
    if ((sym == 'c') && (c = getch()))
        return CLEAR_STACK;
    if (sym == 'C')
        return COSINUS;
    if (sym == 'S')
        return SINUS;
    if (sym == 'e')
        return EXPONENT;
    if ((tolower(sym) == 'd') && (c = getch()))
        return DUPLICATE_STACK;
    if (sym == '^')
        return POW;
    if (c == EOF) {
        ungetch(c);
        is_EOF++;
        return '\n';
    }
    if (!isdigit(c) && c != '.')
        return c;      /* not a number */
    if (isdigit(c))    /* collect integer part */
        while(isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')      /* collect fraction part */
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE];    /* buffer for ungetch */
int bufp = 0;         /* next free position in buf */

int getch(void)  /* get a (possibly pushed-back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)  /* push character back on input */
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

void print_top(void)
{
    if  (sp > 1)
        printf("Top elements of stack: %.8g and %.8g\n", val[sp - 1], val[sp - 2]);
    else if (sp)
        printf("Top element of stack: %.8g\n", val[sp - 1]);
    else
        printf("error: no top element in stack\n");
}

void clear_stack(void)
{
    do {
        val[sp] = 0;
    } while(--sp > 0);
    sp = 0;
    printf("stack has been cleared\n");
}

void duplicate_stack(void)
{
    int tmp_1 = 0, tmp_2 = sp;
    if (sp) {
        do {
            val[tmp_2++] =  val[tmp_1++];
        } while(tmp_1 != sp);
        sp = tmp_2;
        printf("Stack has been duplicated.\n");
    }
    else
        printf("error: nothing to duplicate.\n");
}
/*
 * an example: 
 *              a = 6 b = 5 +
 *                          = 11
 * */
int handle_variables(int c)
{
    if (!isalpha(c))
        return c;
    while (!isdigit(c = getch()) && c != '-' && c != '\n' && c != EOF)
        ;
    return c;
}

