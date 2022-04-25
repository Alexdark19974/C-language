#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>

#define FIELD_SIZE 100
#define ARR_SIZE 100
#define PRECISION_ON 1
#define PRECISION_OFF 0

void minprintf(char *fmt, ...);

int main(void)
{
	int a = 1231;
	int b = 124;
	char c = 'A';
	short s = 10;
	int d = 1354253;
	double f = 10.5;

    minprintf("\t%10d \n%9d %c %h\n %s %.1f\n", a, b, c, s, "Hello, World!", f);

	/*
		В соответствии с ТЗ предоставляю минимальную реализацию функции minprintf:
		1) работает с форматами типа integer, char, char * (string), float/double;
		2) выводит на экран передаваемые значения в соответствии с ключами типа "%10d";
		3) ключи работают только с %d и %f, поскольку это демонстративная версия;
		4) функционал можно расширять, и она будет всё больше и больше становиться похожей на printf;
	*/

    return 0;
}

/* minprintf: ограниченная версия printf
   со списком аргументов переменной длины */

void minprintf(char *fmt, ...)
{
    va_list ap; /* указатель на безымянные аргументы */

    char *p = NULL;
	char *sval = NULL;
	char *f_w_arr = NULL;
	char i = 0;
	char field = 0;
    int ival = 0;
	char cval = 0;
	short hval = 0;
    double dval = 0.0;
	char p_point = 0;

    va_start(ap, fmt); /* установить ap на 1-й аргумент без имени */
    for (p = fmt; *p; p++)
	{
	    if (*p != '%')
		{
			if (field)
        	{
            	;
        	}
			else
			{
		    	putchar(*p);
            	continue;
			}
        }

		if (field)
        {
		   	p+=i;

			field = 0;
			i = 0;
        }

	    switch(*++p)
		{
        	case 'd':
			{
				if (*f_w_arr)
				{
					int num = atoi(f_w_arr);

					switch(num)
					{
						case 10:
						{
                        	ival = va_arg(ap, int);
							printf("%10d", ival);
                   	 		break;
						}
						case 9:
                        {
                            ival = va_arg(ap, int);
                            printf("%9d", ival);
                            break;
                        }
						case 8:
                        {
                            ival = va_arg(ap, int);
                            printf("%8d", ival);
                            break;
                        }
						case 7:
                        {
                            ival = va_arg(ap, int);
                            printf("%7d", ival);
                            break;
                        }
						case 6:
                        {
                            ival = va_arg(ap, int);
                            printf("%6d", ival);
                            break;
                        }
                        case 5:
                        {
                            ival = va_arg(ap, int);
                            printf("%5d", ival);
                            break;
                        }
                        case 4:
                        {
                            ival = va_arg(ap, int);
                            printf("%4d", ival);
                            break;
                        }
                        case 3:
                        {
                            ival = va_arg(ap, int);
                            printf("%3d", ival);
                            break;
                        }
						case 2:
                        {
                            ival = va_arg(ap, int);
                            printf("%2d", ival);
                            break;
                        }
                        case 1:
                        {
                            ival = va_arg(ap, int);
                            printf("%1d", ival);
                            break;
                        }
						default:
						{
							ival = va_arg(ap, int);
							printf("%10d", ival);
						}
					}
					free(f_w_arr);
					f_w_arr = NULL;
					break;
				}
		    	ival = va_arg(ap, int);
            	printf("%d", ival);
            	break;
			}
        	case 'f':
			{
				if (*f_w_arr)
                {
                    int num = atoi(f_w_arr);

                    switch(num)
					{
						case 10:
                		{
							dval = va_arg(ap, double);
                    		printf("%.10f", dval);
                    		break;
                		}
                		case 9:
                		{
							dval = va_arg(ap, double);
             				printf("%.9f", dval);
                			break;
                		}
 						case 8:
                		{
                  			dval = va_arg(ap, double);
		                    printf("%.8f", dval);
		                    break;
		                }
		                case 7:
		                {
		                	dval = va_arg(ap, double);
		                    printf("%.7f", dval);
		                    break;
		                }
		                case 6:
		                {
		                  	dval = va_arg(ap, double);
		                    printf("%.6f", dval);
		                    break;
		                }
		                case 5:
		                {
		                	dval = va_arg(ap, double);
		                    printf("%.5f", dval);
		                    break;
		                }
		                case 4:
		                {
		                	dval = va_arg(ap, double);
		                    printf("%.4f", dval);
		                    break;
		                }
						case 3:
		                {
		                	dval = va_arg(ap, double);
		                    printf("%.3f", dval);
		                    break;
		                }
		                case 2:
		                {
		               		dval = va_arg(ap, double);
		                    printf("%.2f", dval);
		                    break;
		                }
		                case 1:
		                {
		               		dval = va_arg(ap, double);
		                	printf("%.1f", dval);
		                    break;
		                }
		                default:
		                {
		               		dval = va_arg(ap, double);
		                	printf("%f", dval);
							break;
		                }
						p_point = PRECISION_OFF;
						break;
					}
					free(f_w_arr);
					f_w_arr = NULL;
					break;
				}
				dval = va_arg(ap, double);
				printf("%f", dval);
				break;
			}
        	case 's':
			{
            	for (sval = va_arg(ap, char *); *sval; sval++)
				{
                	putchar(*sval);
				}
            	break;
			}
			case 'c':
			{
				cval = (char) va_arg(ap, int);
				printf("%c", cval);
				break;
			}
			case 'h':
			{
				hval = (short) va_arg(ap, int);
				printf("%hu", hval);
				break;
			}
	    	default:
			{
				if (*p == '.')
				{
					p_point = PRECISION_ON;
					p++;
				}
				if (isdigit(*p))
				{
					f_w_arr = calloc(ARR_SIZE, sizeof(char));

					for (char *tmp = p; isdigit(*tmp); tmp++, i++)
					{
						f_w_arr[i] = *tmp;
					}

					f_w_arr[i] = '\0';

					while (*p != ' ' && *p != '\n' && *p != '\t' && *p != '.')
					{
						p--;
					}
					if (p_point == PRECISION_ON)
					{
						i--;
					}
					field = 1;
					break;
				}

				printf("error: undefined specifier");
				exit(EXIT_FAILURE);
            	break;
			}
        }
    }
    va_end(ap); /* заврешающие операции  */
}
