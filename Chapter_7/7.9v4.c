#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "no arguments.Abort.\n");
        exit(EXIT_FAILURE);
    }

    FILE *ifp = NULL;
    FILE *ofp = NULL;
    char c = 0;
    char res = 0;
    unsigned char counter = 0;

    ifp = fopen(argv[1], "r");

    while ((c = getc(ifp)) != EOF)
    {
		(c >= 'A' && c <= 'Z') ? counter++ : counter;
    }

    ofp = fopen(argv[2], "w");
    fprintf(ofp, "The number of upper case letters is %d\n", counter);

    fclose(ofp);
    fclose(ifp);

    printf("Finished.\n");

    exit(EXIT_SUCCESS);
}
