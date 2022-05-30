#include <stdio.h>
#include <unistd.h>

int main(void) /* копирование потока ввода в поток вывода */
{
	char buf[BUFSIZ] = {0};
	int n = 0;

//	printf("BUFSIZ is %d\n", BUFSIZ);

	while ((n = read(0, buf, BUFSIZ)) > 0)
	{
//		printf("bytes received are: %d\n", n);
//		printf("buf is %s\n", buf);
		write(1, buf, n);
//		printf("buf is %s\n", buf);
	}
	return 0;
}
