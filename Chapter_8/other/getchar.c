#include <stdio.h>
#include <unistd.h>

#undef getchar

/* getchar: версия с простой буферизацией */
int getchar(void);

int main(void)
{
	char c = 0;

	while ((c = getchar()) != EOF)
	{
	//	printf("received c is : %c\n", c);
		write(1, &c, 1);
	}

	return 0;
}

int getchar(void)
{
	char c = 0;

	return (read(0, &c, 1) == 1) ? (unsigned char) c : EOF;
}
