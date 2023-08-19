#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAXLINE 1000
#define READ_FROM_STDIN 2
int get_line(char *line, int max);
void find_pattern_from_file(char **argv, int *except, int number);
/* find:  print lines that match pattern from 1st arg */
main(int argc, char *argv[])
{
    char line[MAXLINE];
    long lineno = 0;
    int c, except = 0, number = 0, found = 0, file = 0;
    while(--argc > 0 && (*++argv)[0] /* **++argv */ == '-')
        while ((c = *++argv[0] /* *++(*argv)*/ /* *++(argv[0]) */))
            switch(c) {
                case 'x':
                    except = 1;
                    break;
                case 'n':
                    number = 1;
                    break;
                case 'f':
                    file = 1;
                    break;
                default:
                    fprintf(stderr, "find: illegal option %c\n", c);
                    argc = 0;
                    found = -1;
                    break;
            }
    if (argc != 1 && !file)
        printf("Usage: find -x -n pattern\n");
    else if (found >= 0) {
        if (file) {
            found = except;
            find_pattern_from_file(argv, &except, number);
            if (except == READ_FROM_STDIN) {
                except = found;
                goto read_from_stdin;
            }
        } else {
read_from_stdin:
            while (get_line(line, MAXLINE) > 0) {
                lineno++;
                if ((strstr(line, *argv) != NULL) != except) {
                    if (number)
                        printf("%ld: ", lineno);
                    printf("%s", line);
                    found++;
                }
            }
        }
    }
    return found;
}

void find_pattern_from_file(char **argv, int *except, int number)
{
    int found = 0;
    long lineno = 0;
    FILE *fp;
    size_t len = 0;
    char *strp = NULL;
    char buf[MAXLINE] = {0};

    if (*(argv + 1) == NULL) {
        fprintf(stderr, "no file to read. Read from stdin? y/n ");
        scanf("%c", &buf[0]);
        getchar();
        if (tolower(buf[0]) == 'y')
            *except = READ_FROM_STDIN; // except is reutilized. In a way, this is an exception, too.
        return;
    }
    if (!(len = strlen(*argv))) {
        fprintf(stderr, "failed to calculate the length of %s", *argv);
        goto exit_with_failure;
    }

    if ((strp = malloc(len + 1)) == NULL) {
        fprintf(stderr, "failed to allocate memory for pattern %s\n", *argv);
        perror("calloc");
        goto exit_with_failure;
    }
    strncpy(strp, *argv, len);
    strp[len + 1] = '\0';
    while (*++argv && (fp = fopen(*argv, "r")) != NULL) {
        while (!feof(fp)) {
            fgets(buf, MAXLINE - 1, fp);
            if (ferror(fp)) {
                fprintf(stderr, "error ocurred while reading %s\n", *(argv - 1));
                goto exit_with_failure;
            }
            if ((strstr(buf, strp) != NULL) != *except) {
                if (number)
                    printf("lineno=%ld ", ++lineno);
                printf("line=%s\n", buf);
                found++;
            }
        }
        if (found > 0) {
            if (except)
                printf("file=%s, found everything but %s %d times\n", *argv, strp, found);
            else
                printf("file=%s, found \"%s\" %d times\n", *argv, strp, found);
            found = lineno = 0;
            fclose(fp);
        }
    }
exit_with_failure:
    if (strp)
        free(strp);
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

