#include <stdio.h>
#define BUF 100

int main(void)
{
	double sum = 0.0;
	double op_1 = 0.0;
	double op_2 = 0.0;
	char op_3 = 0;
	char calculus[BUF] = "2 5 *";

	sscanf(calculus, "%lf %lf %c", &op_1, &op_2, &op_3);

	switch (op_3)
	{
		case '+':
		{
			sum = op_1 + op_2;
			break;
		}
		case '-':
		{
			sum = op_1 - op_2;
			break;
		}
		case '*':
		{
			sum = op_1 * op_2;
			break;
		}
		case '/':
		{
			sum = op_1 / op_2;
			break;
		}
	}

	printf("   = %lf\n", sum);

	return 0;
}
