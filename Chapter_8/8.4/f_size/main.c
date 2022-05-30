#include "syscalls.h"
#include "_iob.h"

extern File _iob[OPEN_MAX];

int main(int argc, char *argv[])
{
	char size = 0;

	if (argv[1] != NULL)
	{
		if (atoi(argv[1]) <= 0)
		{
			fprintf(stderr, "error: value can't be 0 or lower.\n");
			exit(EXIT_FAILURE);
		}
		else
		{
			size = atoi(argv[1]);
		}
	}

	File *fp1 = myfopen("input.txt", "r");

//	myfseek(fp1, 2048, SEEK_SET);

	File *fp2 = myfopen("output.txt", "w");
	char c = 0;
	char counter = 0;
//	char status = 0;

	while ((c = getc(fp1)) != EOF)
	{
		/*if (status == 0)
		{
			myfseek(fp1, 1023, SEEK_SET);
			status = 1;
		}*/

 		putc(c, fp2);

		if (argv[1])
		{
			if (++counter == size)
			{
				myfflush(fp2);
				counter = 0;
			}
		}
	}

	if ((myfclose(fp1)) == -1 || myfclose(fp2) == -1)
	{
		fprintf(stderr, "error: failed to close the file\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i != OPEN_MAX; i++)
	{
		if (_iob[i].base != NULL)
		{
			free(_iob[i].base);
			_iob[i].ptr = NULL;
			_iob[i].cnt = 0;
		}
	}
	exit(EXIT_SUCCESS);
}
