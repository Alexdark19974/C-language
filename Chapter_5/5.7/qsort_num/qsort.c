#include <stdio.h>
#include <stdlib.h>
#define MAXDIGIT 1000
void _qsort(int *, int, int);

main()
{
    int i;
    int digits[MAXDIGIT] = {8, 16, 11, 12, 0, 1 -2};
    printf("pre-sorted array: 8, 16, 11, 12, 0, 1 ,-2\n");
    _qsort(digits, 0, 6);
    printf("sorted array:");
    for (i= 0; i < 7; i++) {
        printf(" %d", digits[i]);
    }
    putchar('\n');

    return 0;
}

/* qsort:  sort v[left]...v[right] into increasing order */
void _qsort(int *digits, int left, int right)
{
    int i, last;
    void swap(int *digits, int i, int j);
    if (left >= right)    /* do nothing if array contains */
        return;           /* fewer than two elements */
    swap(digits, left, (left + right)/2);
    last = left;
    for(i = left + 1; i <= right; i++) {
        if (digits[i] < digits[left])
            swap(digits, ++last, i);
    }
    swap(digits ,left, last);
    _qsort(digits, left, last-1);
    _qsort(digits , last+1, right);
}

/* swap:  interchange v[i] and v[j] */
void swap(int *digits, int i, int j)
{
    int temp = 0;

    temp = digits[i];
    digits[i] = digits[j];
    digits[j] = temp;
}
