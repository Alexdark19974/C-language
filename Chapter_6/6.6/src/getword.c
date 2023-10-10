#include "lookup.h"
static char  buf[MAXWORD] = {0};
static int bufp = 0;

/* getword: get next word or character from input */
int getword(char *word, char *defn, int lim)
{
    int c, ret;
    char *w = !*word ? word : defn;
    unsigned char isComment = 0;
    static unsigned char is_preprocessor = 0;
keep_reading:
    while (isspace(c = getch()))
        ;
    if (c != EOF)
        *w++ = c;
    if (c == EOF)
        return EOF;

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
    if (!is_preprocessor && c == '#') {
        is_preprocessor++;
        w = &word[0];
    } else if (is_preprocessor && c == '#' && *word) {   /* take a step back because we need to process the previous define without an explicit value */
        ungetch(c);
        *defn = '1';
        goto exit;
    }
    for ( ; --lim > 0; w++)
        if (isspace(*w = getch())) {
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
    if (is_preprocessor == 1 && !strcmp(word, "define")) {
        is_preprocessor++;
        *word = '\0';
        if (getword(word, defn, lim) == EOF)
            return word[0] = EOF;
        is_preprocessor++;
        if (getword(word, defn, lim) == EOF)
            return word[0] = EOF;
        if (defn[0] == '"') {
            int len = strlen(&defn[1]);
            memmove(defn, &defn[1], len);
            defn[len] = '\0';
        } else if (!isdigit(defn[0]))
            return NESTED_DEFINE;
    } else if (is_preprocessor < 2) {
        is_preprocessor = 0;
        *word = '\0';
        goto keep_reading;
    }
    if (*word && *defn)
        is_preprocessor = 0;
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

