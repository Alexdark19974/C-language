#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAXLINE 1000
#define DIGIT_MAX 11
#define ALPHA_MAX 27
#define ERR -1
int get_line(char line[], int lim);
int expand(char s1[], char s2[]);

main()
{
    int len;
    unsigned int n;
    char line[MAXLINE];
    char expanded_line[MAXLINE];

    for (n = 0; n != MAXLINE; ++n)
        line[n] = expanded_line[n] = 0;

    printf("Enter the line: ");
    while ((len = get_line(line, MAXLINE)) > 0) {
        if (len > 0) {
            n = expand(expanded_line, line);
            if (n != ERR)
                printf("Expanded line: %s\n", expanded_line);
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

int expand(char s1[], char s2[])
{
    int i, j, len, tmp, ctr, ctr2, is_expand;
    char digits[DIGIT_MAX] = "0123456789";
    char upper_chars[ALPHA_MAX] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char lower_chars[ALPHA_MAX] = "abcdefghijklmnopqrstuvwxyz";
    is_expand = tmp = 0;
    len = strlen(s2) - 1;

    for (i = 0; i <= len; ++i) {
        if (isalnum(s2[i])) {
            for (j = i + 1; j <= len; ++j)
                if (s2[j] == '-') {
                    is_expand++;
                    break;
                }
            if (!is_expand) {
                printf("error: expand sign \'-\' not found\n");
                return ERR;
            }
            for (j = len; j >= 0; --j)
                if (i != j && isupper(s2[j]) && !isupper(s2[j - 1])) {
                    if (isdigit(s2[i])) {
                        printf("error: the left border is not a alphabet character.\n");
                        return ERR;
                    }
                    else if (s2[i] > s2[j]) {
                        printf("error: descending order is not supported.\n");
                        return ERR;
                    }
                    ctr = ctr2 = 0;
                    while (s2[i] != upper_chars[ctr2])
                        ctr2++;
                    while (upper_chars[ctr] != s2[j])
                        ctr++;
                    strcpy(s1, upper_chars + ctr2);
                    s1[ctr + 1] = '\0';
                    is_expand = 0;
                    break;
                }
                else if (i != j && islower(s2[j]) && !islower(s2[j - 1])) {
                    if (isdigit(s2[i])) {
                         printf("error: the left border is not a alphabet character.\n");
                         return ERR;
                    }
                    else if (s2[i] > s2[j]) {
                        printf("error: descending order is not supported.\n");
                        return ERR;
                    }
                    ctr = ctr2 = 0;
                    while (s2[i] != lower_chars[ctr2])
                        ctr2++;
                    while (lower_chars[ctr] != s2[j])
                        ctr++;
                    strcpy(s1, lower_chars + ctr2);
                    s1[ctr + 1] = '\0';
                    is_expand = 0;
                    break;
                }
                else if (i != j && isdigit(s2[j]) && !isdigit(s2[j - 1])) {
                    if (isalpha(s2[i])) {
                        printf("error: the left border is not a digit.\n");
                        return ERR;
                    }
                    else if (s2[i] > s2[j]) {
                        printf("error: descending order is not supported.\n");
                        return ERR;
                    }
                    strcpy(s1, digits + (s2[i] - '0'));
                    ctr = 0;
                    while (s1[ctr] != s2[j])
                        ctr++;
                    s1[ctr + 1] = '\0';
                    is_expand = 0;
                    break;
                }
                else
                    tmp++;
            if (is_expand) {
                printf("error: the left border digit not found\n");
                break;
            }
            i = j + tmp;
        }
    }

    return 0;
}

