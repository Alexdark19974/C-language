#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAXLINE     1000
#define LINEBREAK   10
int get_line(char *, int);
void break_string(char *, int);

main()
{
    char str[MAXLINE] = {0};
    int ret = 0, i;

    while ((ret = get_line(str, MAXLINE)) != EOF) {
        if (ret >= LINEBREAK) {
            break_string(str, LINEBREAK);
            printf("Broken string:\n");
            for (i = 0; str[i] != '\0'; i++)
                !isgraph(str[i]) ? str[i] == '\n' ? printf("0x%x\n",str[i]) : printf("0x%x",str[i]) : putchar(str[i]);
        } else {
            printf("Unbroken string:\n");
            for (i = 0; str[i] != '\0'; i++)
                !isgraph(str[i]) ? str[i] == '\n' ? printf("0x%x\n",str[i]) : printf("0x%x",str[i]) : putchar(str[i]);
        }
    }
    return 0;
}


int get_line(char *s, int lim)
{
    int i, c = 0;

    for (i = 0; (i < lim) && ((c = getchar()) != EOF) && (c != '\n'); ++i)
        *(s + i) = c;
    if (c == '\n')
        *(s + i) = c, i++; 
    *(s + i) = '\0';
    return c == EOF ? EOF : i;
}

void break_string(char *str, int lim)
{
    char tmp[MAXLINE] = {0};

    if (str[lim] != '\n' && str[lim] != '\0') {
        strcpy(tmp, &str[lim]);
        str[lim] = '\n';
        str[lim + 1] = '\0';
        strcat(str, tmp);
    } else if (str[lim] == '\n' || str[lim] == '\0')
        return;

    if ((int)(strlen(tmp) - 1) > LINEBREAK)
        break_string(str, lim + LINEBREAK);
}
