#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void filecopy(FILE *ifp, FILE *ofp);

/* cat: concatenate files, version 1 */
main(int argc, char *argv[])
{
#if defined (CAT_CMP)
#define MAXLINE 1000
    void file_cmp(char **);
    if (--argc < 2 || argc > 2) {
        fprintf(stderr, "2 files are required to perform comparison.\n");
        exit(EXIT_FAILURE);
    }
    file_cmp(argv + 1);
    return 0;
#endif
    FILE *fp;
    void filecopy(FILE *, FILE *);
#if defined (CAT_V2)
    char *prog = argv[0];   /* program name for errors */
#endif
    if (argc == 1)  /* no args; copy standard input */
        filecopy(stdin, stdout);
    else
        while (--argc > 0)
            if ((fp = fopen(*++argv, "r")) == NULL) {
#if defined (CAT_V1)
                printf("cat: can't open %s\n", *argv);
                return 1;
#elif defined (CAT_V2)
                fprintf(stderr, "%s: can't open %s\n", prog, *argv);
                exit(1);
#endif
            } else {
                filecopy(fp, stdout);
                fclose(fp);
            }
#if defined (CAT_V2)
    if (ferror(stdout)) {
        fprintf(stderr, "%s: error writing stdout\n", prog);
        exit(2);
    }
    exit(0);
#else
    return 0;
#endif
}

/*filecopy: copy file ifp to file ofp */
void filecopy(FILE *ifp, FILE *ofp)
{
    int c;

    while ((c = getc(ifp)) != EOF)
        putc(c, ofp);
    if (ferror(ifp)) {
        fprintf(stderr, "error occured while readin from file.\n");
        perror("getc");
    }
    if (feof(ifp))
        printf("End of the file is reached.\n");
}

#if defined (CAT_CMP)
void file_cmp(char **argv)
{
    FILE *fp1, *fp2;
    char *tmp_fp1p, *tmp_fp2p;

    if ((fp1 = fopen(*argv++, "r")) == NULL || (fp2 = fopen(*argv, "r")) == NULL) {
        fprintf(stderr, "Failed to open file");
        if (fp1 == NULL)
            fprintf(stderr, " %s", *(argv - 1));
        if (fp2 == NULL)
            fprintf(stderr, " %s", *argv);
        putc('\n', stderr);

        exit(EXIT_FAILURE);
    }

    if ((tmp_fp1p = calloc(1, MAXLINE)) == NULL) {
        fprintf(stderr, "failed to allocate memory for file 1.\n");
        exit(EXIT_FAILURE);
    }
    if ((tmp_fp2p = calloc(1, MAXLINE)) == NULL) {
        fprintf(stderr, "failed to allocate memory for file 2.\n");
        if (tmp_fp1p != NULL)
            free(tmp_fp1p);
        exit(EXIT_FAILURE);
    }

    while (!feof(fp1) && !feof(fp2)) {
        fgets(tmp_fp1p, MAXLINE, fp1);
        fgets(tmp_fp2p, MAXLINE, fp2);

        if (ferror(fp1) || ferror(fp2)) {
            fprintf(stderr, "error while reading file.\n");
            free(tmp_fp1p);
            free(tmp_fp2p);
            exit(EXIT_FAILURE);
        }
        if (strcmp(tmp_fp1p, tmp_fp2p)) {
            printf("diff:\n");
            fputs("from file 1: ", stdout);
            fputs(tmp_fp1p, stdout);
            fputs("from file 2: ", stdout);
            fputs(tmp_fp2p, stdout);
            goto free_all;
        }
    }
    printf("No difference has been found.\n");
free_all:
    free(tmp_fp1p);
    free(tmp_fp2p);
    fclose(fp1);
    fclose(fp2);

}
#endif

