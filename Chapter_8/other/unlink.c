#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		fprintf(stderr, "error: nothing to unlink\n");
        exit(EXIT_FAILURE);
	}
	int n = unlink(argv[1]); // removes the file name and the file itself

	if (n == -1) // if error, then proccess it
	{
		fprintf(stderr, "error: couldn't unlink the file\n");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
