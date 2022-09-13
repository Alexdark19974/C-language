#include <stdio.h>
#include <unistd.h>

#undef getchar

/* версия с простой буферизацией */
int getchar(void);

int main(void)
{
    char c = 0;

    while ((c = getchar()) != EOF)
    {
     // printf("received c is : %c\n", c);
        write(1, &c, 1);
    }

    return 0;
}

int getchar(void)
{
    static char buf[BUFSIZ] = {0};
	static char *bufp = buf;
	static int n = 0;

	if (n == 0) /* буфер пустой */
	{
		n = read(0, buf, sizeof(buf));
		bufp = buf;
	}

    return (--n >= 0) ? (unsigned char) *bufp++: EOF;
}





