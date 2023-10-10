#include "bintree.h"
static char  buf[MAXWORD] = {0};
static int bufp = 0;

int handle_comment_or_preprocessor(unsigned char);

/* getword: get next word or character from input */
int getword(char *word, int lim, unsigned int *line_cnt)
{
    int c, /*ret,*/ getch(void);
    void ungetch(int);
    char *w = word;
    /*unsigned char isComment = 0;*/
    while (isspace(c = getch()))
        ;
    if (c != EOF)
        *w++ = c;
    if (c == EOF)
        return EOF;
    if (c == '#') {
   /*     handle_comment_or_preprocessor(PREPROCESSOR); */
        word[0] = '#';
        goto exit;
    }
/*    if (c != '/' && !isComment && !isalpha(c)) {
        *w = '\0';
        return c;
    } else if (c == '/') {
        isComment++;
         if ((*w = getch()) == '/') {
            handle_comment_or_preprocessor(++isComment);
            return isComment = 0;
         } else {
             --isComment;
             ungetch(*w--);
         }
    } */
    for ( ; --lim > 0; w++)
        if (!isalnum(*w = getch())) {
        /*    if ((isComment == 1 && *w == '/') || *w == '*') {
                if (*w == '/')
                    isComment++;
                else if (*w == '*')
                    isComment = ASTERISK;
                if (END == (ret = handle_comment_or_preprocessor(isComment))) {
                    *(--w) = '\0';
                    printf("preprocessor constant is ignored if any.\n");
                } else if (ERR == ret)
                    return EOF;
                else
                    break;
            } */
            if (*w == '\n')
                *line_cnt+=1;
            ungetch(*w);
            break;
        }
    *w = '\0';
    if (check_if_noise_word(word) == NOISE_WORD) {
        printf("warning: noise word'%s' will be ignored.\n", word);
        word[0] = '\0';
    }
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

int handle_comment_or_preprocessor(unsigned char type)
{
    int c, i;
    char tempbuf[MAXWORD] = {0};
    if (type == COMMENT)
        printf("data after '//' will be ignored.\n");
    if (type == COMMENT || type == PREPROCESSOR) {
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
            printf("data inside '/*...'*/' will be ignored\n");
            return END;
        } else {
            tempbuf[i] = '\0';
            if (c == '/' && (tempbuf[i] = getch()) == '/') {
                handle_comment_or_preprocessor(COMMENT);
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

