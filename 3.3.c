#include <stdio.h>
#define MAX 1000
/*C Program to expand short hand notations like a-z in the string s1 into the equivalent complete list abc—xyz in s2. Allowed for letters of either case and digits, and be prepared to handle cases like a-b-c and a-z0-9 and -a-z. Arranged that a leading or trailing – is taken literally. */
char signed expand (char[], char[]);

int main(void)
{
    char s1[MAX] = "a-b-c-d-e-f-g-h-i-j-k-l-m-n-o-p-q-r-s-t-u-v-w-x-y-z-0-1-2-3-4-5-6-7-8-9";
    char s2[MAX];
    expand(s1,s2);
    printf("%s\n", s2);
    return 0;
}
char signed expand (char s1[], char s2[])
{
    int i = 0;
    int j = 0;
    int trailing_sign = 0;
    int leading_sign = 0;

    for (i = 0; s1[i] != '\0'; i++)
    {
        switch(s1[i])
        {
            case '-' :
            {
                if (s1[0] == '-' && !trailing_sign)
                {
                    s2[j++] = '-';
                    s2[j++] = ' ';
                    i++;
                    trailing_sign = 1;
                }
                if (s1[i - 1] >= 'a' && s1[i + 1] <= 'z' || s1[i - 1] >= 'A' && s1[i + 1] <= 'Z' || s1[i - 1] >= '0' && s1[i + 1] <= '9')
                {
                    for (char count = s1[i - 1]; count <= s1[i + 1];count++)
                    {
                        if (s2[j - 2] == count)
                        {
                            ++count;
                        }
                        s2[j++] = count;
                        s2[j++] = ' ';
                    }
                    i++;
                }
                if (s1[i] == '-' && s1[i + 1] == '\0' && !leading_sign)
                    {
                        s2[j++] = '-';
                        i++;
                        leading_sign = 1;
                    }
                break;
            }
            default :
            break;
        }
    }
    s2[j] = s1[i];
}