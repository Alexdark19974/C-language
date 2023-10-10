#include "lookup.h"
static char  buf[MAXWORD] = {0};
static int bufp = 0;

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
    int c, ret;
    char *w = word;
    unsigned char isComment = 0;
keep_reading:
    while (isspace(c = getch()))
        ;
    if (c != EOF)
        *w++ = c;
    if (c == EOF)
        return EOF;

/*    if (c != '/' && !isComment && !isalpha(c)) {
        *w = '\0';
        return c;
    } */ 
    if (c == '/') {
        isComment++;
         if ((*w = getch()) == '/') {
            if (ERR == handle_comment(++isComment))
                return EOF;
            word[0] = '/', word[1] = '/';
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
                    sprintf(word, "//");
                    goto exit;
                } else if (ERR == ret || EOF == ret)
                    return EOF;
                else {
                    w = word;
                    goto keep_reading;
                }
            }
            ungetch(*w);
            break;
        }
    *w = '\0';
exit:
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

int handle_comment(unsigned char type)
{
    int c, i;
    char tempbuf[MAXWORD] = {0};
    if (type == COMMENT)
        printf("data after '//' will be ignored.\n");
    if (type == COMMENT) {
        while ((c = getch()) != '\n' && c != EOF)
            ;
    } else {
        for (i = 0; i < MAXWORD && (c = tempbuf[i] = getch()) != '*' && c != '/' && c != '\n' &&c != EOF; i++)
            ;
        if (i >= MAXWORD) {
            printf("error: buffer overflow\n");
            return ERR;
        }
        if (c == '*' && (tempbuf[i] = getch()) == '/') {
            printf("data inside '/*'...'*/' will be ignored\n");
            if ((c = getch()) == '\n') {
                return END;
            } else if (c == EOF) {
                return EOF;
            } else {
                ungetch(c);
                return CONTINUE;
            }
        } else {
            tempbuf[i] = '\0';
            if (c == '/' && (tempbuf[i] = getch()) == '/') {
                handle_comment(COMMENT);
                tempbuf[i] = '\0';
            }
            printf("warning: no closing comment '*/', therefore, the string will keep being processed.\n");
            for (i = i - 1; i >= 0; i--) {
                ungetch(tempbuf[i]);
            }
        }
    }
    return END;
}

