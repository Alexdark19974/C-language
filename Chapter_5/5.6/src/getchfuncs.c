#include "5.6.h"

int bufp = 0;
char buf[BUFSIZ] = {0};

int getch(void)
{
    return (bufp > 0) ? *(buf + (--bufp)) : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZ)
        printf("ungetch: too many characters\n");
    else
        *(buf + bufp++) = c;
}
/* Potentially, getop() may handle numbers >9 but it is not required by the exercise. */
int getop(char *s)
{
    int c = 0;
try_again:
    while ((*s = c = getch()) == ' ' || c == '\t') ;
    *(s + 1) = '\0';
    if (!isdigit(*s)) {
        printf("REMAINDER: only digits can be accepted.\n");
        goto try_again;
    }
    getch();
    return *s;
}
