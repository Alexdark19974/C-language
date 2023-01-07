#include <stdio.h>
#define MAXLINE 1000
#define MAXELEMENT 10
int get_line(char line[], int lim);
int atoi(char s[]);
int rand(void);
int binsearch(int x, int v[], int n);
void srand(unsigned int seed);
void linear_sort(int v[], int n);
void swap(int v1[], int v2[], int i);

unsigned long int next = 1;

main()
{
    int len;
    unsigned int x, n;
    int v[MAXELEMENT];
    char line[MAXLINE];

    srand(1);

    for (n = 0; n != MAXLINE; ++n) {
        line[n] = 0;
        if (n < MAXELEMENT)
            v[n] = rand();
    }
    /* binary search works only in an array that's been sorted */
    linear_sort(v, MAXELEMENT);

    for (n = 0; n != MAXELEMENT; ++n)
        printf("%d ", v[n]);
    putchar('\n');

    printf("Enter the number: ");
    while ((len = get_line(line, MAXLINE)) > 0) {
        if (len > 0) {
            x = atoi(line);
            printf("number: %d\n", x);
            x = binsearch(x, v, MAXELEMENT);
            (x == -1) ? printf("No match\n") : printf("Match at index=%d\n", x);
        }
    }

    return 0;
}

int get_line(char line[], int lim)
{
    int i, c;

    c = 0;
    for (i=0;i<lim-1 && (c = getchar())!=EOF && c!='\n'; ++i)
        line[i] = c;

    if (c == '\n')
        line[i++] = c;

    line[i] = '\0';
    return i;
}

int atoi(char s[])
{
    int i, n;

    n = 0;
    for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i)
        n = 10 * n + (s[i] - '0');
    return n;
}

/* srand:  set seed for rand() */
void srand(unsigned int seed)
{
    next = seed;
}

/* rand:  return pseudo-random integer on 0..32767 */
int rand(void)
{
    next = next * 1103515245 + 12345;
    return (unsigned int) (next/65536) % 100;
}

/* binsearch: find x in v[0] <= v[1] <= ... <= v[n-1] */
int binsearch(int x, int v[], int n)
{
    int low, high, mid;

    low = mid = 0;
    high = n - 1;

    while (low <= high && (x != (v[mid = ((low + high) / 2)]))) {
        if (x < v[mid])
            high = mid - 1;
        else
            low = mid + 1;
        /* if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        */
        //else    /* found match */
        //    return mid;
    }
    return (v[mid] == x) ? mid : -1;  /* no match */
}

void linear_sort(int v[], int n)
{
    int i, is_sorted;
    for (i = is_sorted = 0; is_sorted <= (n - 1); ++i) {
        if ((i < (n - 1)) && v[i] > v[i + 1]) {
            swap(v, v, i);
            is_sorted--;
        }
        else if (i == (n - 1))
            i = -1;
        else
            is_sorted++;
    }
}

void swap(int v1[], int v2[], int i)
{
    int tmp;

    tmp = v1[i];
    v1[i] = v2[i + 1];
    v2[i + 1] = tmp;
}
