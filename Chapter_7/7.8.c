#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAXLINE 1000
#define READ_AND_PRINT_FROM_STDIN 2
int get_line(char *line, int max);
void print_file(char **argv, int *except, int number);
/* find:  print lines that match pattern from 1st arg */
main(int argc, char *argv[])
{
    char line[MAXLINE];
    long lineno = 0;
    int c, except = 0, number = 0, file = 0;
    while(--argc > 0 && (*++argv)[0] /* **++argv */ == '-')
        while ((c = *++argv[0] /* *++(*argv)*/ /* *++(argv[0]) */))
            switch(c) {
                case 'n':
                    number = 1;
                    break;
                case 'f':
                    file = 1;
                    break;
                default:
                    fprintf(stderr, "find: illegal option %c\n", c);
                    argc = 0;
                    c = -1;
                    break;
            }
    if (argc != 1 && !file)
        printf("Usage: print -n file1 file2 file3\n");
    else if (c >= 0){
        if (file) {
            print_file(argv, &except, number);
            if (except == READ_AND_PRINT_FROM_STDIN)
                goto read_and_print_from_stdin;
        } else {
read_and_print_from_stdin:
            while (get_line(line, MAXLINE) > 0) {
                lineno++;
                if (number)
                    printf("%ld: ", lineno);
                printf("%s", line);
            }
        }
    }
    return c;
}

void print_file(char **argv, int *except, int number)
{
    long lineno = 0, page = 0;
    FILE *fp;
    char buf[MAXLINE] = {0};

    if (*argv == NULL) {
        fprintf(stderr, "no file to read and print. Read from stdin? y/n ");
        scanf("%c", &buf[0]);
        getchar();
        if (tolower(buf[0]) == 'y')
            *except = READ_AND_PRINT_FROM_STDIN; // except is reutilized. In a way, this is an exception, too.
        return;
    }

    while (*argv && (fp = fopen(*argv++, "r")) != NULL) {
        printf("-----------------%s---------------------\n", *(argv - 1));
        while (!feof(fp)) {
            fgets(buf, MAXLINE - 1, fp);
            if (ferror(fp)) {
                fprintf(stderr, "error ocurred while reading %s\n", *(argv - 1));
                goto exit_with_failure;
            }
            if (number)
                printf("lineno=%ld ", ++lineno);
            fputs(buf, stdout);
        }
        lineno = 0;
        printf(">>>>>>>>>>>>>PAGE=%ld<<<<<<<<<<<<<<<\n", ++page);
        printf("---------------------------------------\n\n");
        fclose(fp);
    }
exit_with_failure:
    exit(EXIT_FAILURE);
}

int get_line(char *s, int lim)
{
    int i, c = 0;

    for (i = 0; (i < lim) && ((c = getchar()) != EOF) && c != '\n'; ++i)
        *(s + i) = c;
    if (c == '\n')
        *(s + i) = c, i++; 
    *(s + i) = '\0';
    return c == EOF ? EOF : i;
}

