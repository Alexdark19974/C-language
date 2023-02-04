#include <stdio.h>
#include <stdlib.h>  /* for atof() */
#include <math.h>
#include <ctype.h>

#define MAXLINE 1000
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
int getop(char [], char[]);
int get_line(char [], int lim);
void push(double);
double pop(void);
void print_top(void);
void clear_stack(void);
void duplicate_stack(void);
int handle_variables(char []);
int is_EOF = 0;
int i = 0;
/* reverse Polish calculator */
main()
{
    int type, len;
    double op2;
    char s[MAXOP] = {0};
    char digit[MAXOP] = {0};
    printf(": ");

    while ((len = get_line(s, MAXLINE)) > 0) {
        while (len && (type = getop(s, digit)) != EOF) {
            switch (type) {
                case PRINT_TOP:
                    print_top();
                    if (is_EOF)
                        goto normal_exit;
                    printf(": ");
                    break;
                case CLEAR_STACK:
                    clear_stack();
                    if (is_EOF)
                        goto normal_exit;
                    printf(": ");
                    break;
                case DUPLICATE_STACK:
                    duplicate_stack();
                    printf(": ");
                    if (is_EOF)
                        goto normal_exit;
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
                    push(atof(digit));
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
                    if (is_EOF)
                        goto normal_exit;
                    len = i = 0;
                    printf(": ");
                    break;
                default:
                    if (!isspace(type))
                        printf("error: unknown command %s\n", s);
                    break;
            }
        }
    }
normal_exit:
    printf("Exited by \"goto\" statement\n");
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


int get_line(char s[], int lim)
{
    int j, c;

    c = 0;
    for (j = 0; j < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++j)
        s[j] = c;
    if (c == '\n')
        s[j++] = c;
    if (c == EOF) {
        s[j++] = '\n';
        is_EOF++;
    }
    s[j] = '\0';
    return j;
}

/* getop:  get next character or numeric operand */
int getop(char s[], char digit[])
{
    int j = 0, sym, is_variable;
    while ((s[i]) == ' ' || s[i] == '\t')
       i++;
    is_variable = handle_variables(s);
    sym = is_variable;
    if (sym == '-' && !isdigit(s[++i]))
        return sym;
    else if (sym == '-' && isdigit(s[i]))
        digit[j++] = sym;
    if ((tolower(sym)) == 't')
        return PRINT_TOP;
    if (sym == 'c')
        return CLEAR_STACK;
    if (sym == 'C')
        return COSINUS;
    if (sym == 'S')
        return SINUS;
    if (sym == 'e')
        return EXPONENT;
    if ((tolower(sym) == 'd') && (s[++i]))
        return DUPLICATE_STACK;
    if (sym == '^' && (s[++i]))
        return POW;
    if (!isdigit(s[i]) && s[i] != '.')
        return s[i++];      /* not a number */
    if (isdigit(s[i]))    /* collect integer part */
        while (isdigit(s[i]))
            digit[j++] = s[i++];
    if (s[i] == '.') {     /* collect fraction part */
        digit[j++] = s[i++];
        while (isdigit(s[i]))
            digit[j++] = s[i++];
    }
    digit[j] = '\0';
    return NUMBER;
}

void print_top(void)
{
    if (is_EOF)
        putchar('\n');
    if  (sp > 1)
        printf("Top elements of stack: %.8g and %.8g\n", val[sp - 1], val[sp - 2]);
    else if (sp)
        printf("Top element of stack: %.8g\n", val[sp - 1]);
    else
        printf("error: no top element in stack\n");
}

void clear_stack(void)
{
    if (is_EOF)
        putchar('\n');
    do {
        val[sp] = 0;
    } while(--sp > 0);
    sp = 0;
    printf("stack has been cleared\n");
}

void duplicate_stack(void)
{
    int tmp_1 = 0, tmp_2 = sp;
    if (is_EOF)
        putchar('\n');
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
int handle_variables(char s[])
{
    int j = i;
    if (!isalpha(s[i]))
        return s[i];
    while (!isdigit(s[++i]) && s[i] != '-' && s[i] != '\n' && s[i] != EOF)
        ;
    return (isdigit(s[i]) ? s[i] : s[j]);
}

