#include <stdio.h>
#define MAXLINE 1000
#define MAXELEMENT 10
int get_line(char line[], int lim);
void escape(char s[], char t[]);
void un_escape(char s[], char t[]);

main()
{
    int len;
    unsigned int n;
    char line[MAXLINE];
    char esc_line[MAXLINE];

    for (n = 0; n != MAXLINE; ++n)
        line[n] = esc_line[n] = 0;

    printf("Enter the line: ");
    while ((len = get_line(line, MAXLINE)) > 0) {
        if (len > 0) {
            escape(esc_line, line);
            printf("Escaped line: %s\n", esc_line);
            for (n = 0; line[n] != 0; ++n)
                line[n] = 0;
            un_escape(line, esc_line);
            printf("Un-escaped line: %s\n", line);
        }
        printf("Enter the line: ");
    }

    return 0;
}

int get_line(char line[], int lim)
{
    int i, c;

    c = 0;
    for (i=0;i<lim-1 && (c = getchar())!=EOF && c!='\n'; ++i)
        line[i] = c;

    if (c == '\n')
        line[i++] = c;

    line[i] = '\0';
    return i;
}

void escape(char s[], char t[])
{
    int i, j;

    for (i = 0, j = 0; t[i] != '\0'; ++i, ++j) {
        switch(t[i]) {
            case '\n':
                s[j++] = '\\';
                s[j] = 'n';
                break;
            case '\t':
                s[j++] = '\\';
                s[j] = 't';
                break;
            default:
                s[j] = t[i];
                break;
        }
    }
    s[j] = '\0';
}

void un_escape(char s[], char t[])
{
    int i, j;

    for (i = 0, j = 0; t[i] != '\0'; ++i, ++j) {
        switch(t[i]) {
            case '\\':
                if (t[i + 1] == 'n') {
                    s[j] = '\n';
                    i++;
                }
                else if (t[i + 1] == 't') {
                    s[j] = '\t';
                    i++;
                }
                break;
            default:
                s[j] = t[i];
                break;
        }
    }
    s[j] = '\0';
}

