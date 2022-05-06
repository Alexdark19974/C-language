#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char is_upper(char);

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
    unsigned char counter = 0;

    ifp = fopen(argv[1], "r");

    while ((c = getc(ifp)) != EOF)
    {
        if (is_upper(c))
        {
            counter++;
        }
    }

    ofp = fopen(argv[2], "w");
    fprintf(ofp, "The number of upper case letters is %d\n", counter);

    fclose(ofp);
    fclose(ifp);

    printf("Finished.\n");

    exit(EXIT_SUCCESS);
}

char is_upper(char c)
{
    return (c >= 'A' && c <= 'Z');
}

