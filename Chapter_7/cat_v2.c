#include <stdio.h>
#include <stdlib.h>

/* cat: сцепление файлов по порядку, версия 2 */

int main (int argc, char *argv[])
{
    FILE *fp = NULL;
    void filecopy(FILE *, FILE*);
	char *prog = argv[0]; /* имя программы для сообщений */

    if (argc == 1) /*нет аргументов; стандартный поток*/
    {
        filecopy(stdin, stdout);
    }
    else
    {
        while (--argc > 0)
        {
            if ((fp = fopen(*++argv, "r")) == NULL)
            {
                fprintf(stderr,"%s: can't open %s\n", prog, *argv);
                exit(1);
            }
            else
            {
                filecopy(fp, stdout);
                fclose(fp);
                fp = NULL;
            }
        }
    }
	if (ferror(stdout))
	{
		fprintf(stderr, "%s: error writing stdout\n", prog);
		exit(2);
	}

    exit(0);
}

/* filecopy: копирование файла ifp в файл ofp */
void filecopy(FILE *ifp, FILE *ofp)
{
    int c = 0;

    while ((c = getc(ifp)) != EOF)
    {
        putc(c, ofp);
    }
}

