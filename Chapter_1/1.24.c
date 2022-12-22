#include <stdio.h>

#define MAXLINE 1000    /* maximum input line size */
#define TABSTOP 8
#define FOLDPOINT 16
#define ERR -1
int max;            /* maximum length seen so far */
char line[MAXLINE];     /* current input line */
char longest[MAXLINE];  /* longest line saved here */
char no_comment_line[MAXLINE];
int get_line(void);
void copy(void);
int check_syntax(void);
/* print longest input line */
main()
{
    int len;
    extern int max;
    extern char longest[];

    max = 0;
    while ((len = get_line()) > 0)
        if (len > 0) {
            max = len;
            copy();
            max = check_syntax();
            if (max < 0)
                printf("SYNTAX CHECK FAILED!\n");
            else {
                printf("SYNTAX CHECK OK: %s", line);
            }
        }
    return 0;
}

/* getline: read a line into s, return length */
int get_line(void)
{
    int c, i;
    extern char line[];

    for (i=0; i<MAXLINE-1 && (c = getchar()) != EOF && c!='\n'; i++)
        line[i] = c;
    if (c == '\n') {
        line[i] = c;
        ++i;
    }
    line[i] = '\0';
    return i;
}

/* copy: sepcialized version */
void copy(void)
{
    int i;
    extern char line[], longest[];

    i = 0;
    while ((longest[i] = line[i]) != '\0')
        ++i;
}
/* Rudimentary syntax checker: ugly but it does the job */
int check_syntax(void)
{
    int i, j, len, isComment, isRoundb, isSquareb, isParenth, isSingleq, isDoubleq, isLinecomment;

    i = j = len = isComment = isLinecomment = isRoundb = isSquareb = isParenth = isSingleq = isDoubleq = 0;
    while (longest[len] != '\0')
        ++len;
    while (i >= 0 && i < len && longest[i] != '\0') {
        if (longest[i] == '/' && longest[i + 1] == '*' && !isLinecomment) {
            ++isComment; j = len;
            while (j > 0) {
                if (longest[j - 1] == '*' && longest[j] == '/') {
                    --isComment; j = -1; i+=2;
                }
                --j;
            }
            if (!j) {
                i = -2; isComment = -1;
            }
        }
        else if (longest[i] == '*' && longest[i + 1] == '/' && !isLinecomment) {
            if (j != -2)
                --isComment;
        }
        else if (longest[i] == '/' && longest[i + 1] == '/') {
            ++isLinecomment; i = -2;
        }
        else if (longest[i] == '/' && longest[i + 1] != '/' && longest[i + 1] != '*' /*&& longest[i + 1] != '\n'*/) {
            if (j != -2)
                --isLinecomment;
        }
        else if (longest[i] == ')' && !isLinecomment)
            --isRoundb;
        else if (longest[i] == ']' && !isLinecomment)
            --isSquareb;
        else if (longest[i] == '}' && !isLinecomment)
            --isParenth;
        else if (longest[i] == '(' && !isLinecomment)
            ++isRoundb;
        else if (longest[i] == '[' && !isLinecomment)
            ++isSquareb;
        else if (longest[i] == '{' && !isLinecomment)
            ++isParenth;
        else if (longest[i] == '\'')
            ++isSingleq;
        else if (longest[i] == '\"')
            ++isDoubleq;
        ++i;
    }

    if (isRoundb > 0 || isRoundb < 0 || isSquareb > 0 || isSquareb < 0 || isParenth > 0 || isParenth < 0) {
        printf("Syntax: '(', '[', '{' or ')', ']', '}' is missing.\n"); i = ERR;
    }
    if (isComment > 0 || isComment < 0) {
        printf("Syntax: '/*' or '*/' is missing.\n"); i = ERR; 
    }
    if (isLinecomment < 0) {
        printf("Syntax: '/' is missing.\n"); i = ERR;
    }
    if (isLinecomment > 0)
        i = 0;
    if (isSingleq % 2 != 0 || isDoubleq % 2 != 0) {
        printf("Syntax: \' or \" is missing\n"); i = ERR;
    }
    return i;
}
