#include "wordcount.h"

static char  buf[MAXWORD] = {0};
static int bufp = 0;

int handle_comment(unsigned char);

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
    int c, ret, getch(void);
    void ungetch(int);
    char *w = word;
    unsigned char isComment = 0;
    while (isspace(c = getch()))
        ;
    if (c != EOF)
        *w++ = c;
    if (c == '#') {
        if (isalpha(*w = getch())) {
            c = *(w - 1) = *w;
            printf("preprocessor constant detected.\n");
        }
    }
    if (c != '/' && !isComment && !isalpha(c)) {
        *w = '\0';
        return c;
    } else if (c == '/') {
        isComment++; 
         if ((*w = getch()) == '/') {
            handle_comment(++isComment);
            return isComment = 0;
         } else {
             --isComment;
             ungetch(*w--);
         }
    }
    for ( ; --lim > 0; w++)
        if (!isalnum(*w = getch())) {
            if ((isComment == 1 && *w == '/') || *w == '*') {
                if (*w == '/')
                    isComment++;
                else if (*w == '*')
                    isComment = ASTERISK;
                if (END == (ret = handle_comment(isComment))) {
                    *(--w) = '\0';
                    printf("preprocessor constant is ignored if any.\n");
                } else if (ERR == ret)
                    return EOF;
                else
                    break;
            }
            ungetch(*w);
            break;
        }
    *w = '\0';
    return word[0];
}

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

int handle_comment(unsigned char isComment)
{
    int c, i;
    char tempbuf[MAXWORD] = {0};
    if (isComment == 2) {
        while ((c = getch()) != '\n' && c != EOF)
            ;
        printf("data after '//' will be ignored.\n");
    } else {
        for (i = 0; i < MAXWORD && (c = tempbuf[i] = getch()) != '*' && c != '/' && c != '\n' &&c != EOF; i++)
            ;
        if (i >= MAXWORD) {
            printf("error: buffer overflow\n");
            return ERR;
        }
        if (c == '*' && (tempbuf[i] = getch()) == '/') {
            printf("data inside '/*...'*/' will be ignored\n");
            return END;
        } else {
            tempbuf[i] = '\0';
            if (c == '/' && (tempbuf[i] = getch()) == '/') {
                handle_comment(isComment = 2);
                tempbuf[i] = '\0';
            }
            printf("warning: no closing comment '*/', therefore, the string will keep being processed.\n");
            for (i = i - 1; i >= 0; i--) {
                ungetch(tempbuf[i]);
            }
        }
    }
    return 0;
}

