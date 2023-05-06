#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <ctype.h>
#define MAXOPS 1000
#define MAXDIGITS 1000
#define MAXSTRING 1000
#define TRUE 1
#define FALSE 0

int getop(char *);
int expr(char **argv);
int calc_ratio(char **argv);
double pop(double *, int *);
void push(double *, char *, int *);
void evaluate(double *, char **, int, int);
void add_brackets(int, char);
void exit_on_sig(int);
enum { ERR = -1, NUMBER = 1, OP = 2, FLOAT = 3 };

main(int argc, char *argv[])
{
    if (argc < 4)
        return printf("Usage: -f 2 3 +\n");
    signal(SIGSEGV, exit_on_sig);
    if (ERR == calc_ratio(argv + 1)|| ERR == expr(argv))
            goto error;
    return 0;
error:
    return printf("Exited with an error.\n");
}

int expr(char **argv)
{
    double digits[MAXDIGITS] = {0.0};
    int i = 0, opt = 0, is_float = 0;

    while(*++argv) {
        switch(opt = getop(*argv)) {
            case NUMBER:
                push(digits, *argv, &i);
                break;
            case OP:
                goto evaluate_me;
            case FLOAT:
                is_float = TRUE;
                break;
            default:
                printf("Error: unknown value=%s\n", *argv);
                goto error;
                break;
        }
    }
evaluate_me:
    if (i <= 1)
        goto error;
    evaluate(digits, argv, i, is_float);
    return 0;
error:
    return ERR;
}

int getop(char *argv)
{
    char actionType = 0;

    if (isdigit(*argv) && (isdigit(*(argv + 1)) || *(argv + 1) == '.' || *(argv + 1) == '\0'))
        actionType = NUMBER;
    else if (!strcmp(argv, "-f"))
        actionType = FLOAT;
    else if (!isdigit(*argv) && (*argv == '+' || *argv == '-' || *argv == '*' || *argv == '/') && *(argv + 1) == '\0')
        actionType = OP;
    else if (!isdigit(*argv) && isdigit(*(argv + 1)))
        actionType = NUMBER;
    else
        actionType  = ERR;
    return actionType;
}

double pop(double *arrp, int *i)
{
    *i = *i - 1;
    double tmp = *(arrp + *i);

    return tmp;
}

void push(double *arrp, char *argv, int *i)
{
    *(arrp + *i) = atof(argv);
    *i = *i + 1;
}

void evaluate(double *digits, char **ops, int i, int is_float)
{
    double buf[MAXSTRING] = {0.0};
    int idx = 0, tmp_ops = 0;
    /*we write the whole expression to buf backwards including operations without brackets*/
    while (i) {
        buf[idx++] = pop(digits, &i);
        if (*ops != NULL) {
            if (**ops == '-' && *(*ops + 1) != '\0') {
                if (*(*ops + 1) == 'f') { // check if there's "floating" option
                    is_float = TRUE;
                    break;
                } else
                    goto error;
            }
            tmp_ops++;
            buf[idx++] = **ops++;
        }
    }
    i = --idx;
    /* we read the expression from the end because we applied stack-like push() and pop() functions + LIFO
      the end result is 2 5 10 + \* becomes 2 * (5 + 10) */
    printf("expr: ");
    do {
        if (tmp_ops > 1 && i != idx && idx) // skip the first num (we don't need "(5)" ), then add a bracket if necessary
            add_brackets(tmp_ops, '(');
        is_float == TRUE ? printf("%.2lf", buf[idx--]) : printf("%d",(int)buf[idx--]);
        if (idx < 0)
            break;
        printf(" %c ",(char)buf[idx--]);
    } while(idx >= 0);
    if (tmp_ops > 1)
        add_brackets(tmp_ops - 1, ')'); // add brackets in while loop if necessary
    putchar('\n');
    return;
error:
    printf("error: option %s is not available.\n", *ops);
}

void exit_on_sig(int sig_num)
{
    switch(sig_num)
    {
        case SIGSEGV:
            printf("SIGSEGV: access to unavailable memory area.\n");
            break;
        default:
            printf("Signal %d received\n", sig_num);
            break;
    }
}

void add_brackets(int bracket_num, char bracket)
{
    if (bracket == ')')
        while (bracket_num--)
            putchar(')');
    else
        putchar('(');
}

int calc_ratio(char **argv)
{
    int digits = 0, ops = 0;

    while (*argv != NULL && isdigit(**argv++))
        digits++;
    argv--;
    while (*argv != NULL && argv++ != NULL)
        ops++;
    if (!ops || !((digits - ops) % 2)) {
        printf("error: unbalanced number of args.\n");
        return ERR;
    }
    return 0;
}
