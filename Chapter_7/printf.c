#include <stdio.h>

int main(void)
{

	char *string = "Hello,";

	printf("1) No elements in between:\n:%s:", string);

	puts("");

	printf("2) Minimal field length is 10, filling the void with blanks on the left:\n:%10s:", string);

	puts("");

	char *string_2 = "Hello, World";

	printf("3) Precision after floating point or max number of chars is 10:\n:%.10s:", string_2);

	puts("");

	printf("4) Minimal field length is 10, filling the void with blans on the right:\n :%-10s:", string);

	puts("");

	printf("5) Precision after floating point or max number of chars is 15:\n:%.15s:", string);

	puts("");

	printf("6) Minimal field length is 15, filling the void with blans on the right:\n:%-15s:", string_2);

	puts("");

	printf("7) Minimal field length is 15, filling the void with blans on the left:\nPrecision after floating point or max number of chars is 15:\n%15.10s", string_2);

	puts("");

	printf("8) Minimal field length is 15, filling the void with blans on the right:\nPrecision after floating point or max number of chars is 15:\n%-15.10s", string_2);

	puts("");

	return 0;
}
