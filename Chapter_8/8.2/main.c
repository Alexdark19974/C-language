#include "syscalls.h"
#include "_iob.h"

extern File _iob[OPEN_MAX];

int main(void)
{
	File *fp1 = myfopen("input.txt", "r");
	File *fp2 = myfopen("output.txt", "w");
	char c = 0;

	while ((c = getc(fp1)) != EOF)
	{
 		putc(c, fp2);
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
